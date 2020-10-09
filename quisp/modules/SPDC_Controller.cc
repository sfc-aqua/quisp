/** \file SPDC_Controller.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/25
 *
 *  \brief SPDC_Controller
 */
#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <modules/EntangledPhotonPairSource.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace quisp {
namespace modules {

// How about if two nodes have imbalanced buffers?
// Maybe use unused qnic (which is ought to be used for another path)?

/** \class SPDC_Controller SPDC_Controller.cc
 *  \todo Documentation of the class header.
 *
 *  \brief SPDC_Controller
 */
class SPDC_Controller : public cSimpleModule {
 private:
  int address;
  int neighbor_address;
  int neighbor_address_two;
  int neighbor_buffer;
  int neighbor_buffer_two;
  int max_buffer;
  double distance_to_neighbor;  // in km
  double distance_to_neighbor_two;  // in km
  double accepted_rate_one;
  double accepted_rate_two;
  double max_accepted_rate;
  double frequency;
  cMessage *generatePacket;
  double timing_buffer;
  // double max_neighbor_distance;//in km
  // double accepted_burst_interval;//in s
  double speed_of_light_in_channel;
  EntangledPhotonPairSource *epps;
  EmitPhotonRequest *emt;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual cModule *getNextNode(cModule *epps, int index, std::string type);  // Find a module (type) connected through the channel
  virtual cModule *getNode(std::string type);  // Find the parent with a specific type
  virtual void checkNeighborsAddress();
  virtual void checkNeighborsDistance();
  virtual void checkNeighborsHoMCapacity();
  virtual void checkNeighborsBuffer();
  virtual double calculateTimeToTravel(double distance, double c);
  virtual EPPStimingNotifier *generateNotifier(double distance_to_neighbor, double c, int destAddr);
  virtual void startPump();
};

Define_Module(SPDC_Controller);

void SPDC_Controller::initialize() {
  frequency = par("frequency");
  cModule *pump = getParentModule()->getSubmodule("PairSource");
  epps = check_and_cast<EntangledPhotonPairSource *>(pump);
  address = par("address");
  timing_buffer = par("timing_buffer");
  cPar *c = &par("Speed_of_light_in_fiber");
  speed_of_light_in_channel = c->doubleValue();
  // For simplicity, I assume the SPDC can access those neighbor information without classical communication but directly.
  checkNeighborsAddress();
  checkNeighborsDistance();
  checkNeighborsHoMCapacity();
  checkNeighborsBuffer();

  // Notify the timing.
  // generatePacket = new cMessage("nextPacket");
  // scheduleAt(simTime(),generatePacket);
}

void SPDC_Controller::handleMessage(cMessage *msg) {
  if (msg == generatePacket) {
    // Or just emit entangled photons without telling the neighbors?
    // Then the neighbor can analyze the intervaland adjust its emission accordingly.
    EPPStimingNotifier *pk, *pkt;
    pk = generateNotifier(distance_to_neighbor, speed_of_light_in_channel, neighbor_address);
    pkt = generateNotifier(distance_to_neighbor_two, speed_of_light_in_channel, neighbor_address_two);
    try {
      send(pk, "toRouter_port");  // send to port out. connected to local routing module (routing.localIn).
      send(pkt, "toRouter_port");
    } catch (std::exception &e) {
      error("Error in SPDC_Controller.cc. It does not have port named toRouter_port.");
      endSimulation();
    }
    startPump();
  } else if (dynamic_cast<EmitPhotonRequest *>(msg) != nullptr) {
    epps->emitPhotons();
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne");
    scheduleAt(simTime() + max_accepted_rate, st);
  } else if (dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg) != nullptr) {
    epps->emitPhotons();
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne");
    scheduleAt(simTime() + max_accepted_rate, st);
  }
  delete msg;
}

void SPDC_Controller::startPump() {
  // for(int i=0; i<max_buffer; i++){
  //   emt = new  EmitPhotonRequest();
  //   scheduleAt(simTime()+timing_buffer+(max_accepted_rate*i), emt);
  // }
  emt = new EmitPhotonRequest("EmitPhotonRequest");
  scheduleAt(simTime() + timing_buffer + (max_accepted_rate), emt);
}

EPPStimingNotifier *SPDC_Controller::generateNotifier(double distance_to_neighbor, double c, int destAddr) {
  EPPStimingNotifier *pk = new EPPStimingNotifier("EppsTimingNotifier");
  double time_to_reach = calculateTimeToTravel(distance_to_neighbor, c);

  // When the packet reaches = simitme()+time
  double time_to_travel = calculateTimeToTravel(distance_to_neighbor, speed_of_light_in_channel);

  // This packet will get received by the node before "time_buffer" seconds.
  double first_arrival_time = timing_buffer;
  pk->setTiming_at(first_arrival_time);
  pk->setKind(4);
  pk->setNumber_of_qubits(max_buffer);
  pk->setInterval(max_accepted_rate);
  pk->setSrcAddr(address);
  pk->setDestAddr(destAddr);
  EV << "!!!!!!!!!!!!!!!!!!!!!!!!!!neighbor_address=" << neighbor_address;
  return pk;
}

cModule *SPDC_Controller::getNextNode(cModule *epps, int index, std::string type) {
  std::string node;
  cGate *currentGate = getParentModule()->gate("quantum_port$o", index)->getNextGate();
  try {
    node = "networks." + type;
    const char *array = node.c_str();
    cModuleType *NodeType = cModuleType::get(array);  // Assumes the node in a network has a type QNode
    while (currentGate->getOwnerModule()->getModuleType() != NodeType) {
      currentGate = currentGate->getNextGate();
    }
    return currentGate->getOwnerModule();
  } catch (std::exception &e) {
    error("No module %s type found. Have you changed the type name in ned file?", node.c_str());
    endSimulation();
  }
  return currentGate->getOwnerModule();
}

void SPDC_Controller::checkNeighborsDistance() {
  cModule *epps = getNode("SPDC");
  try {
    distance_to_neighbor = epps->gate("quantum_port$o", 0)->getChannel()->par("distance");
    distance_to_neighbor_two = epps->gate("quantum_port$o", 1)->getChannel()->par("distance");
  } catch (std::exception &e) {
    error("SPDC could not find parameter distance in channel.");
  }
  try {
    par("distance_to_neighbor") = distance_to_neighbor;
    par("distance_to_neighbor_two") = distance_to_neighbor_two;
  } catch (std::exception &e) {
    error("Parameter not found in SPDC_Controller::checkNeighborDistance");
  }
}

void SPDC_Controller::checkNeighborsAddress() {
  // First, check the node address of neighbors and their channel length.
  cModule *epps = getNode("SPDC");
  cModule *neighbor_one = getNextNode(epps, 0, "QNode");
  neighbor_address = neighbor_one->par("address");
  cModule *neighbor_two = getNextNode(epps, 1, "QNode");
  neighbor_address_two = neighbor_two->par("address");

  try {
    par("neighbor_address") = neighbor_address;
    par("neighbor_address_two") = neighbor_address_two;
  } catch (std::exception &e) {
    error("parameter not found in SPDC_Controller initialize()");
  }
}

// Store the buffer size
void SPDC_Controller::checkNeighborsBuffer() {
  cModule *epps = getNode("SPDC");
  cModule *neighbor_qnic_one = getNextNode(epps, 0, "interHoM")->getParentModule();
  neighbor_buffer = neighbor_qnic_one->par("numBuffer");
  par("neighbor_buffer") = neighbor_buffer;
  cModule *neighbor_qnic_two = getNextNode(epps, 1, "interHoM")->getParentModule();
  neighbor_buffer_two = neighbor_qnic_two->par("numBuffer");
  par("neighbor_buffer_two") = neighbor_buffer_two;
  max_buffer = std::min(neighbor_buffer, neighbor_buffer_two);  // Adjust to the slower one
  par("max_buffer") = max_buffer;
}

// Store the frequency to adjust the emission rate.
void SPDC_Controller::checkNeighborsHoMCapacity() {
  cModule *epps_node = getNode("SPDC");
  cModule *neighbor_interHoM_one = getNextNode(epps_node, 0, "interHoM");
  double temp = neighbor_interHoM_one->getSubmodule("Controller")->par("photon_detection_per_sec");
  accepted_rate_one = (double)1 / (double)neighbor_interHoM_one->getSubmodule("Controller")->par("photon_detection_per_sec");
  cModule *neighbor_interHoM_two = getNextNode(epps_node, 1, "interHoM");
  double tempt = neighbor_interHoM_two->getSubmodule("Controller")->par("photon_detection_per_sec");
  accepted_rate_two = (double)1 / (double)neighbor_interHoM_two->getSubmodule("Controller")->par("photon_detection_per_sec");

  EV << tempt << "- - - - -" << accepted_rate_two << ",,,,,,,,,,," << accepted_rate_one << " - - - " << temp << "\n";
  max_accepted_rate = std::max(accepted_rate_one, accepted_rate_two);  // Needs to adjust to the slower device
  // Adjust pump frequency to the lower HoM detection rate by neighbors.
  // if detection rate is better than emission rate.
  double pump_rate = (double)1 / (double)frequency;
  EV << "Self's rate is 1/" << frequency << " = " << pump_rate;
  if (pump_rate > max_accepted_rate) {  // If HoM detection rate is faster than pump
    max_accepted_rate = pump_rate;  // Now frequency is limited by SPDC pump rate
  }
  par("accepted_burst_interval") = max_accepted_rate;
}

cModule *SPDC_Controller::getNode(std::string type) {
  cModule *currentModule = getParentModule();  // We know that Connection manager is not the QNode, so start from the parent.
  try {
    std::string node = "networks." + type;
    const char *array = node.c_str();
    cModuleType *QNodeType = cModuleType::get(array);  // Assumes the node in a network has a type QNode
    while (currentModule->getModuleType() != QNodeType) {
      currentModule = currentModule->getParentModule();
    }
    return currentModule;
  } catch (std::exception &e) {
    error("No module with SPDC type found. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

double SPDC_Controller::calculateTimeToTravel(double distance, double c) { return (distance / c); }

}  // namespace modules
}  // namespace quisp
