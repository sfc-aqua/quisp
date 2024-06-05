#pragma once

#include <omnetpp.h>
#include <string>
#include "Configuration.h"

namespace quisp_test {
namespace channel_type {

using namespace omnetpp;

class TestChannelType : public cChannelType {
 private:
  cProperties *props;
  cConfiguration *cfg;

 public:
  TestChannelType(const char *name) : cChannelType(name) {
    using quisp_test::configuration::Configuration;
    cfg = new Configuration;
    props = new cProperties;
  }

  cChannel* createChannelObject() override { return nullptr; };
  void addParametersTo(cChannel *channel) override{};
   void applyPatternAssignments(cComponent *component) override{};
  // void setupGateVectors(cModule *module) override{};
  // void buildInside(cModule *module) override{};

  // methods redefined from cComponentType
   cProperties *getProperties() const override { return props; };
   cProperties *getParamProperties(const char *paramName) const override { return nullptr; };
   cProperties *getGateProperties(const char *gateName) const override { return nullptr; };
   cProperties *getSubmoduleProperties(const char *submoduleName, const char *submoduleType) const override { return nullptr; };
   cProperties *getConnectionProperties(int connectionId, const char *channelType) const override { return nullptr; };
   std::string getPackageProperty(const char *name) const override { return std::string("mock package property"); };
   const char *getImplementationClassName() const override { return "TestModuleType"; };
   std::string getCxxNamespace() const override { return std::string("mock namespace"); };
 #if OMNETPP_VERSION >= 0x600 && OMNETPP_BUILDNUM > 1531
   std::string getCxxNamespaceForType(const char *type) const override { return "mock cxx namespace"; };
 #endif

  const char *getSourceFileName() const override { return "no source"; };
  bool isInnerType() const override { return false; };

  std::string str() const override { return "test module type"; };
  std::string getNedSource() const override { return ""; };
};

}  // namespace channel_type
}  // namespace quisp_test
