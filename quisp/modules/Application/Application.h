/*
 * Application.h
 *
 *  Created on: Sep 11, 2020
 *      Author: zigen
 */

#ifndef MODULES_APPLICATION_H_
#define MODULES_APPLICATION_H_

#include "IApplication.h"
#include "modules/Logger/LoggerBase.h"
#include "utils/ComponentProvider.h"

using namespace omnetpp;

namespace quisp {
namespace modules {

/** \class Application Application.cc
 *
 *  \brief Application
 */
class Application : public IApplication, public Logger::LoggerBase {
 public:
  Application();
  ~Application() {}

 protected:
  int my_address;
  bool is_initiator;

  std::unordered_map<int, int> end_node_weight_map;

  void initialize() override;
  void handleMessage(cMessage *msg) override;

  void createEndNodeWeightMap();
  void generateTraffic();

  messages::ConnectionSetupRequest *createConnectionSetupRequest(int dest_addr, int num_of_required_resources);
  utils::ComponentProvider provider;
};

Define_Module(Application);
}  // namespace modules
}  // namespace quisp

#endif /* MODULES_APPLICATION_H_ */
