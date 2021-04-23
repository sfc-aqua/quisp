/** \file Queue.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief Queue
 */

#include "Queue.h"

namespace quisp {
namespace modules {

void Queue::initialize() {
  queue.setName("queue");

  end_transmission_event = new cMessage("endTxEvent");

  if (par("useCutThroughSwitching")) {
    gate("line$i")->setDeliverOnReceptionStart(true);
  }

  frame_capacity = par("frameCapacity");

  qlen_signal = registerSignal("qlen");
  busy_signal = registerSignal("busy");
  queuing_time_signal = registerSignal("queueingTime");
  drop_signal = registerSignal("drop");

  tx_bytes_signal = registerSignal("txBytes");
  rx_bytes_signal = registerSignal("rxBytes");

  emit(qlen_signal, queue.getLength());
  emit(busy_signal, false);
  is_busy = false;
}

void Queue::startTransmitting(cMessage *msg) {
  EV_INFO << "Starting transmission of " << msg << endl;
  is_busy = true;
  int64_t num_bytes = check_and_cast<cPacket *>(msg)->getByteLength();

  EV_DEBUG << "here.....1\n";
  send(msg, "line$o");  // inout gate's output

  EV_DEBUG << "here.....2\n";
  emit(tx_bytes_signal, (long)num_bytes);

  EV_DEBUG << "here.....3\n";

  // Schedule an event for the time when last bit will leave the gate.
  simtime_t transmission_finish_time = gate("line$o")->getTransmissionChannel()->getTransmissionFinishTime();
  EV_INFO << "Transmission will end in " << transmission_finish_time << "\n";

  // pass end_transmission_event when it ends
  scheduleAt(transmission_finish_time, end_transmission_event);
}

void Queue::handleMessage(cMessage *msg) {
  if (hasGUI()) {
    bubble("Queue received a message!\n");
  }

  if (msg == end_transmission_event) {  // update busy status
    // Transmission finished, we can start next one.
    EV_INFO << "Transmission finished.\n";
    is_busy = false;

    if (queue.isEmpty()) {
      emit(busy_signal, false);
      return;
    }

    msg = (cMessage *)queue.pop();
    emit(queuing_time_signal, simTime() - msg->getTimestamp());
    emit(qlen_signal, queue.getLength());
    startTransmitting(msg);
    return;
  }

  if (msg->arrivedOn("line$i")) {
    emit(rx_bytes_signal, (long)check_and_cast<cPacket *>(msg)->getByteLength());
    send(msg, "out");
    return;
  }

  // arrived on gate "in"
  EV_INFO << "Arrived on gate Queue in.....";

  if (end_transmission_event->isScheduled()) {
    EV_INFO << "Currently busy! queue it up\n";

    // We are currently busy, so just queue up the packet.
    if (frame_capacity && queue.getLength() >= frame_capacity) {
      EV_INFO << "Received " << msg << " but transmitter busy and queue full: discarding\n";
      emit(drop_signal, (long)check_and_cast<cPacket *>(msg)->getByteLength());
      delete msg;
      return;
    }

    EV_INFO << "Received " << msg << " but transmitter busy: queuing up\n";
    msg->setTimestamp();
    queue.insert(msg);
    emit(qlen_signal, queue.getLength());
    return;
  }

  // We are idle, so we can start transmitting right away.
  EV_INFO << "Received " << msg << endl;
  emit(queuing_time_signal, SIMTIME_ZERO);
  startTransmitting(msg);
  emit(busy_signal, true);
}

void Queue::finish() { delete end_transmission_event; }

void Queue::refreshDisplay() const {
  getDisplayString().setTagArg("t", 0, is_busy ? "transmitting" : "idle");
  getDisplayString().setTagArg("i", 1, is_busy ? (queue.getLength() >= 3 ? "red" : "yellow") : "");
}

}  // namespace modules
}  // namespace quisp
