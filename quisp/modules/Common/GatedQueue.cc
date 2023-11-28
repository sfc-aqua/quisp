
#include "GatedQueue.h"


using quisp::modules::Logger::LoggerBase;


namespace quisp::modules {

GatedQueue::GatedQueue() : provider(utils::ComponentProvider{this}) {}


void GatedQueue::initialize() {
   Queue::initialize();
   is_busy = false;
   initializeLogger(provider);
}

void GatedQueue::handleMessage(cMessage *msg)
{
    if (hasGUI()) {
        bubble("GatedQueue received a message!\n");
      }

    if (auto vco = dynamic_cast<VisCheckOutcome *>(msg)) {
           if (vco->getNext_check_time() == 0) {
               pending_vcr = false;
               msg = (cMessage *)queue.pop();
               emit(queuing_time_signal, simTime() - msg->getTimestamp());
               emit(qlen_signal, queue.getLength());
               startTransmitting(msg);
           } else {
               VisCheckRetry* retry = new VisCheckRetry();
               next_check_time = vco->getNext_check_time();
               scheduleAfter(next_check_time,retry);
           }
          delete vco;
           return;
        }

    if (dynamic_cast<VisCheckRetry *>(msg)) {
        VisCheckRequest* vis_check = new VisCheckRequest();
        vis_check->setOut_gate(gate("line$o")->getNextGate()->getName());
        vis_check->setIndex(gate("line$o")->getNextGate()->getIndex());
        send(vis_check,"to_ps");
        delete msg;
        return;
    }

    if (msg->arrivedOn("line$i")) {
        emit(rx_bytes_signal, (long)check_and_cast<cPacket *>(msg)->getByteLength());
        send(msg, "out");
        return;
      }




    if (msg == end_transmission_event) {  // update busy status
        // Transmission finished, we can start next one.
        EV_INFO << "Transmission finished.\n";
        is_busy = false;

        if (queue.isEmpty()) {
          emit(busy_signal, false);
          return;
        }

        if (!is_busy and !queue.isEmpty()) {
        is_busy = true;
        VisCheckRequest* vis_check = new VisCheckRequest();
        vis_check->setOut_gate(gate("line$o")->getNextGate()->getName());
        vis_check->setIndex(gate("line$o")->getNextGate()->getIndex());
        send(vis_check,"to_ps");
        }
    return;
    }

    if (frame_capacity && queue.getLength() >= frame_capacity) {
          EV_INFO << "Received " << msg << " but transmitter busy and queue full: discarding\n";
          emit(drop_signal, (long)check_and_cast<cPacket *>(msg)->getByteLength());
          delete msg;
          return;
        }

    EV_INFO << "Received " << msg << ": queuing up\n";
    msg->setTimestamp();
    logger->logPacket("DummyLabel", msg);
    queue.insert(msg);
    emit(qlen_signal, queue.getLength());

    if (!is_busy and !queue.isEmpty() and !pending_vcr) {
    pending_vcr = true;
    VisCheckRequest* vis_check = new VisCheckRequest();
    vis_check->setOut_gate(gate("line$o")->getNextGate()->getName());
    vis_check->setIndex(gate("line$o")->getNextGate()->getIndex());
    send(vis_check,"to_ps");
    }
}

} //namespace
