/** \file dummyModule.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/25
 *
 *  \brief dummyModule
 */

#include <omnetpp.h>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class dummyModule dummyModule.cc
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
