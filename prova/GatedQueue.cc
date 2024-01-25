
#include "GatedQueue.h"
#include "messages/gatedqueue_messages_m.h"

using messages::GQ_ctrl;


Define_Module(GatedQueue);

void GatedQueue::initialize() {
   Queue::initialize();
   visibility_established = new cMessage("VisEstablished");
}

void GatedQueue::handleMessage(cMessage *msg)
{
if (hasGUI()) {
     //  bubble("Queue received a message!\n");
     }

     if (auto ctrl = dynamic_cast<GQ_ctrl *>(msg)) {
         GQ_ctrl* cpy_for_remote = ctrl->dup();
         cpy_for_remote->setIs_copy(true);
        if (gate_open) {
            if (!ctrl->getIs_copy()) send(cpy_for_remote,"line$o");
            setGate_open(ctrl->getCtrl_signal());  // If the gate is already open, send the closing message then close.
            bubble("closing gate");
        } else {                                   // If it is closed, open then send the opening message.
            scheduleAt(simTime(),visibility_established); // I am having this message bypass the queue because it's important ctrl info but I'm not sure I can, TODO: ask
            setGate_open(ctrl->getCtrl_signal());
            if (!ctrl->getIs_copy()) send(cpy_for_remote,"line$o");
            bubble("opening gate");
        }
        EV_INFO << "Gate now " << gate_open;
        delete ctrl;
        return;
     }


     if (msg == end_transmission_event || msg == visibility_established) {  // update busy status
     // Transmission finished, we can start next one.
       EV_INFO << "Transmission finished.\n";
       is_busy = false;

       if (queue.isEmpty()) {
         emit(busy_signal, false);
         return;
       }

       if (gate_open) {
       msg = (cMessage *)queue.pop();
       emit(queuing_time_signal, simTime() - msg->getTimestamp());
       emit(qlen_signal, queue.getLength());
       startTransmitting(msg);
       }
       return;
     }

     if (msg->arrivedOn("line$i")) {
       emit(rx_bytes_signal, (long)check_and_cast<cPacket *>(msg)->getByteLength());
       send(msg, "out");
       return;
     }

     // arrived on gate "in"
     EV_INFO << "Arrived on gate Queue in.....";

     if (end_transmission_event->isScheduled() || !gate_open) { //OR THE GATE IS CLOSED
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
     emit(busy_signal, true);}

void GatedQueue::setGate_open(const bool ctrl_signal) {
    gate_open = ctrl_signal;
    return;
}

