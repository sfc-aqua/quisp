/** \file dummyModule.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/25
 *
 *  \brief dummyModule
 */
#include <PhotonicQubit_m.h>
#include <classical_messages_m.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class dummyModule dummyModule.cc
 *  \todo Documentation of the class header.
 *
 *  \brief dummyModule
 */
class dummyModule : public cSimpleModule {
 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
};

Define_Module(dummyModule);

void dummyModule::initialize() {}
void dummyModule::handleMessage(cMessage *msg) { delete msg; }

}  // namespace modules
}  // namespace quisp
