/** \file ConnectionManager.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief ConnectionManager
 */
#include <vector>
#include <omnetpp.h>
#include <classical_messages_m.h>

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace modules {

/** \class ConnectionManager ConnectionManager.cc
 *  \todo Documentation of the class header.
 *
 *  \brief ConnectionManager
 */
class ConnectionManager : public cSimpleModule
{
    private:
        int myAddress;
    protected:
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
};

Define_Module(ConnectionManager);

void ConnectionManager::initialize()
{
  EV<<"ConnectionManager booted\n";
}

void ConnectionManager::handleMessage(cMessage *msg){

    if(dynamic_cast<ConnectionSetupRequest *>(msg)!= nullptr){
       ConnectionSetupRequest *pk = check_and_cast<ConnectionSetupRequest *>(msg);


       int actual_dst = pk->getActual_destAddr();
    }


}

} // namespace modules
} // namespace quisp
