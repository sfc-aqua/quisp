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
 public:
  Application();
  ~Application() {}

 protected:
  int my_address;

  std::vector<int> other_end_node_addresses;
  bool is_e2e_connection; /**< Does this simulation require end-to-end connection setup?*/
  int number_of_resources;
  int num_measure; /**< The number of measurement between end nodes.*/
  int traffic_pattern; /**< A type of traffic generation.
                        * - 0: No traffic
                        * - 1: From one end node node to random partner node (1 to 1)
                        * - 2: From all end nodes to random partner nodes (n to n)
                        */

  void initialize() override;
  void handleMessage(cMessage *msg) override;

  void storeEndNodeAddresses();
  int getOneRandomEndNodeAddress();

  messages::ConnectionSetupRequest *createConnectionSetupRequest(int dest_addr, int num_of_required_resources);
  utils::ComponentProvider provider;

  simsignal_t signal_init_request;
};

Define_Module(Application);
}  // namespace modules
}  // namespace quisp

#endif /* MODULES_APPLICATION_H_ */
