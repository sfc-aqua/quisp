/** \todo header Write doxygen file header. */
/** \todo clean Clean code when it is simple. */
/** \todo doc Write doxygen documentation. */
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "../PhotonicQubit_m.h"


using namespace omnetpp;

class Queue:  public cSimpleModule{
    private:
        long frameCapacity;
        cQueue queue;
        cMessage *endTransmissionEvent;
        bool isBusy;

        simsignal_t qlenSignal;
        simsignal_t busySignal;
        simsignal_t queueingTimeSignal;
        simsignal_t dropSignal;
        simsignal_t txBytesSignal;
        simsignal_t rxBytesSignal;
    public:
        Queue();

    protected:
      virtual void initialize() override;
      virtual void finish() override;
      virtual void handleMessage(cMessage *msg) override;
      virtual void refreshDisplay() const override;
      virtual void startTransmitting(cMessage *msg);
};

Define_Module(Queue);

Queue::Queue()
{
    endTransmissionEvent = nullptr;
}


void Queue::initialize()
{
    queue.setName("queue");
    endTransmissionEvent = new cMessage("endTxEvent");

    if (par("useCutThroughSwitching"))
        gate("line$i")->setDeliverOnReceptionStart(true);

    frameCapacity = par("frameCapacity");

    qlenSignal = registerSignal("qlen");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingTime");
    dropSignal = registerSignal("drop");
    txBytesSignal = registerSignal("txBytes");
    rxBytesSignal = registerSignal("rxBytes");

    emit(qlenSignal, queue.getLength());
    emit(busySignal, false);
    isBusy = false;

}

void Queue::startTransmitting(cMessage *msg)
{
    EV << "Starting transmission of " << msg << endl;
    isBusy = true;
    int64_t numBytes = check_and_cast<cPacket *>(msg)->getByteLength();

    EV << "here.....1\n";
    send(msg, "line$o");//inout gate's output
    EV << "here.....2\n";
    emit(txBytesSignal, (long)numBytes);
    EV << "here.....3\n";
    //Schedule an event for the time when last bit will leave the gate.
    simtime_t endTransmission = gate("line$o")->getTransmissionChannel()->getTransmissionFinishTime();
    EV<<"Transmission will end in "<<endTransmission<<"\n";
    scheduleAt(endTransmission, endTransmissionEvent);//pass End tansmission message when it ends
}

void Queue::handleMessage(cMessage *msg)
{
    if (hasGUI()) {
        bubble("Queue received a message!\n");
    }

    if (msg == endTransmissionEvent) {//update busy status
        // Transmission finished, we can start next one.
        EV << "Transmission finished.\n";
        isBusy = false;
        if (queue.isEmpty()) {
            emit(busySignal, false);
        }
        else {
            msg = (cMessage *)queue.pop();
            emit(queueingTimeSignal, simTime() - msg->getTimestamp());
            emit(qlenSignal, queue.getLength());
            startTransmitting(msg);
        }
    }
    else if (msg->arrivedOn("line$i")) {
        // pass up
        emit(rxBytesSignal, (long)check_and_cast<cPacket *>(msg)->getByteLength());
        send(msg, "out");
    }
    else {  // arrived on gate "in"
        EV<<"Arrived on gate Queue in.....";

        if (endTransmissionEvent->isScheduled()) {
            EV<<"currrently busy! queue it up\n";
            // We are currently busy, so just queue up the packet.
            if (frameCapacity && queue.getLength() >= frameCapacity) {
                EV << "Received " << msg << " but transmitter busy and queue full: discarding\n";
                emit(dropSignal, (long)check_and_cast<cPacket *>(msg)->getByteLength());
                delete msg;
            }
            else {
                EV << "Received " << msg << " but transmitter busy: queueing up\n";
                msg->setTimestamp();
                queue.insert(msg);
                emit(qlenSignal, queue.getLength());
            }
        }
        else {
            // We are idle, so we can start transmitting right away.
            EV << "\nReceived " << msg << endl;
            emit(queueingTimeSignal, SIMTIME_ZERO);
            startTransmitting(msg);
            emit(busySignal, true);
        }
    }

}

void Queue::finish(){
    delete endTransmissionEvent;
}

void Queue::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 0, isBusy ? "transmitting" : "idle");
    getDisplayString().setTagArg("i", 1, isBusy ? (queue.getLength() >= 3 ? "red" : "yellow") : "");
}


