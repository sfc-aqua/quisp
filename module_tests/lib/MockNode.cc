#include "omnetpp.h"
using namespace omnetpp;
class MockNode : public cSimpleModule {
 public:
  MockNode();
  ~MockNode();

 protected:
  virtual void initialize();
  virtual void finish();
  virtual void handleMessage(cMessage *msg);
};
Define_Module(MockNode);

MockNode::MockNode() {}
MockNode::~MockNode() {}
void MockNode::initialize() {}
void MockNode::handleMessage(cMessage *msg) {}
void MockNode::finish() {}
