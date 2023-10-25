#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Transceiver : public cSimpleModule
{
  protected:
    simsignal_t received_photon_ID;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};
