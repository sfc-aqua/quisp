/*
 * Application.h
 *
 *  Created on: Sep 11, 2020
 *      Author: zigen
 */

#ifndef MODULES_APPLICATION_H_
#define MODULES_APPLICATION_H_

#include "IApplication.h"
#include "utils/ComponentProvider.h"

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class Application Application.cc
 *
 *  \brief Application
 */
class Application : public IApplication {
 private:
  int my_address;

  int *other_end_node_addresses;
  int num_of_other_end_nodes;
  bool is_e2e_connection;
  int number_of_resources;
  int num_measure;

  void initialize() override;
  void handleMessage(cMessage *msg) override;

  int *storeEndNodeAddresses();
  int getOneRandomEndNodeAddress();
  cModule *getQNode();

  ConnectionSetupRequest *createConnectionSetupRequest(int dest_addr, int num_of_required_resources);

 public:
  Application();
  int getAddress();
  utils::ComponentProvider provider;
};

Define_Module(Application);
}  // namespace modules
}  // namespace quisp

#endif /* MODULES_APPLICATION_H_ */
