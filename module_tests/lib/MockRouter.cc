#include "omnetpp.h"
using namespace omnetpp;
class MockRouter : public cSimpleModule {
 public:
  MockRouter();
  ~MockRouter();

 protected:
  virtual void initialize();
  virtual void finish();
  virtual void handleMessage(cMessage *msg);
};
Define_Module(MockRouter);

MockRouter::MockRouter() {}
MockRouter::~MockRouter() {}
void MockRouter::initialize() {}
void MockRouter::handleMessage(cMessage *msg) {}
void MockRouter::finish() {}
