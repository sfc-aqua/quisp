/*
 * Application.h
 *
 *  Created on: Sep 11, 2020
 *      Author: zigen
 */

#ifndef MODULES_APPLICATION_H_
#define MODULES_APPLICATION_H_

#include <classical_messages_m.h>
#include <omnetpp.h>

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class Application Application.cc
 *
 *  \brief Application
 */
class Application : public cSimpleModule {
 private:
  int my_address;

  int *other_end_node_addresses;
  int num_of_other_end_nodes;
  bool is_e2e_connection;
  int number_of_resources;
  int num_measure;

  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;

  virtual int *storeEndNodeAddresses();
  virtual int getOneRandomEndNodeAddress();
  virtual cModule *getQNode();

  ConnectionSetupRequest *createConnectionSetupRequest(int dest_addr, int num_of_required_resources);

 public:
  Application();
  int getAddress();
};

Define_Module(Application);
}  // namespace modules
}  // namespace quisp

#endif /* MODULES_APPLICATION_H_ */
