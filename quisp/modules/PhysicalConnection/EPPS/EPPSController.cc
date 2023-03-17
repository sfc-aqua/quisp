/** \file EPPSController.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/25
 *
 *  \brief EPPSController
 */
#include <PhotonicQubit_m.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <vector>

#include "EntangledPhotonPairSource.h"

using namespace omnetpp;

namespace quisp {
namespace modules {

// How about if two nodes have imbalanced buffers?
// Maybe use unused qnic (which is ought to be used for another path)?

/** \class EPPSController EPPSController.cc
 *
 *  \brief EPPSController
 */
class EPPSController : public cSimpleModule {
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
  virtual void checkNeighborsBSACapacity();
  virtual void checkNeighborsBuffer();
  virtual double calculateTimeToTravel(double distance, double c);
  virtual EPPStimingNotifier *generateNotifier(double distance_to_neighbor, double c, int destAddr);
  virtual void startPump();
};

Define_Module(EPPSController);

void EPPSController::initialize() {
  frequency = par("frequency");
  cModule *pump = getParentModule()->getSubmodule("PairSource");
  epps = check_and_cast<EntangledPhotonPairSource *>(pump);
  address = par("address");
  timing_buffer = par("timing_buffer");
  cPar *c = &par("speed_of_light_in_fiber");
  speed_of_light_in_channel = c->doubleValue();
  // For simplicity, I assume the SPDC can access those neighbor information without classical communication but directly.
  checkNeighborsAddress();
  checkNeighborsDistance();
  checkNeighborsBSACapacity();
  checkNeighborsBuffer();

  // Notify the timing.
  // generatePacket = new cMessage("nextPacket");
  // scheduleAt(simTime(),generatePacket);
}

void EPPSController::handleMessage(cMessage *msg) {
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
      error("Error in EPPSController.cc. It does not have port named toRouter_port.");
      endSimulation();
    }
    startPump();
  } else if (dynamic_cast<EmitPhotonRequest *>(msg)) {
    epps->emitPhotons();
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne");
    scheduleAt(simTime() + max_accepted_rate, st);
  } else if (dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg)) {
    epps->emitPhotons();
    SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne");
    scheduleAt(simTime() + max_accepted_rate, st);
  }
  delete msg;
}

void EPPSController::startPump() {
  // for(int i=0; i<max_buffer; i++){
  //   emt = new  EmitPhotonRequest();
  //   scheduleAt(simTime()+timing_buffer+(max_accepted_rate*i), emt);
  // }
  emt = new EmitPhotonRequest("EmitPhotonRequest");
  scheduleAt(simTime() + timing_buffer + (max_accepted_rate), emt);
}

EPPStimingNotifier *EPPSController::generateNotifier(double distance_to_neighbor, double c, int destAddr) {
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

cModule *EPPSController::getNextNode(cModule *epps, int index, std::string type) {
  std::string node;
  cGate *currentGate = getParentModule()->gate("quantum_port$o", index)->getNextGate();
  try {
    node = "modules." + type;
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

void EPPSController::checkNeighborsDistance() {
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
    error("Parameter not found in EPPSController::checkNeighborDistance");
  }
}

void EPPSController::checkNeighborsAddress() {
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
    error("parameter not found in EPPSController initialize()");
  }
}

// Store the buffer size
void EPPSController::checkNeighborsBuffer() {
  cModule *epps = getNode("SPDC");
  cModule *neighbor_qnic_one = getNextNode(epps, 0, "BSAInternal")->getParentModule();
  neighbor_buffer = neighbor_qnic_one->par("num_buffer");
  par("neighbor_buffer") = neighbor_buffer;
  cModule *neighbor_qnic_two = getNextNode(epps, 1, "BSAInternal")->getParentModule();
  neighbor_buffer_two = neighbor_qnic_two->par("num_buffer");
  par("neighbor_buffer_two") = neighbor_buffer_two;
  max_buffer = std::min(neighbor_buffer, neighbor_buffer_two);  // Adjust to the slower one
  par("max_buffer") = max_buffer;
}

// Store the frequency to adjust the emission rate.
void EPPSController::checkNeighborsBSACapacity() {
  cModule *epps_node = getNode("SPDC");
  cModule *neighbor_BSAInternal_one = getNextNode(epps_node, 0, "BSAInternal");
  double temp = neighbor_BSAInternal_one->getSubmodule("Controller")->par("photon_detection_per_sec");
  accepted_rate_one = (double)1 / (double)neighbor_BSAInternal_one->getSubmodule("Controller")->par("photon_detection_per_sec");
  cModule *neighbor_BSAInternal_two = getNextNode(epps_node, 1, "BSAInternal");
  double tempt = neighbor_BSAInternal_two->getSubmodule("Controller")->par("photon_detection_per_sec");
  accepted_rate_two = (double)1 / (double)neighbor_BSAInternal_two->getSubmodule("Controller")->par("photon_detection_per_sec");

  EV << tempt << "- - - - -" << accepted_rate_two << ",,,,,,,,,,," << accepted_rate_one << " - - - " << temp << "\n";
  max_accepted_rate = std::max(accepted_rate_one, accepted_rate_two);  // Needs to adjust to the slower device
  // Adjust pump frequency to the lower BSA detection rate by neighbors.
  // if detection rate is better than emission rate.
  double pump_rate = (double)1 / (double)frequency;
  EV << "Self's rate is 1/" << frequency << " = " << pump_rate;
  if (pump_rate > max_accepted_rate) {  // If BSA detection rate is faster than pump
    max_accepted_rate = pump_rate;  // Now frequency is limited by SPDC pump rate
  }
  par("accepted_burst_interval") = max_accepted_rate;
}

cModule *EPPSController::getNode(std::string type) {
  cModule *currentModule = getParentModule();  // We know that Connection manager is not the QNode, so start from the parent.
  try {
    std::string node = "modules." + type;
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

double EPPSController::calculateTimeToTravel(double distance, double c) { return (distance / c); }

}  // namespace modules
}  // namespace quisp
