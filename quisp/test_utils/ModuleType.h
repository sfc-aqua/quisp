#pragma once

#include <omnetpp.h>
#include "Configuration.h"
#include "omnetpp/cconfiguration.h"
#include "omnetpp/cproperties.h"
using namespace omnetpp;
namespace quisp_test {

class TestModuleType : public cModuleType {
 private:
  cProperties *props;
  cConfiguration *cfg;

 public:
  cModule *createModuleObject() override{};

  void addParametersAndGatesTo(cModule *module) override{};

  void applyPatternAssignments(cComponent *component) override{};

  void setupGateVectors(cModule *module) override{};

  void buildInside(cModule *module) override{};

  // methods redefined from cComponentType
  cProperties *getProperties() const override { return props; };
  cProperties *getParamProperties(const char *paramName) const override{};
  cProperties *getGateProperties(const char *gateName) const override{};
  cProperties *getSubmoduleProperties(const char *submoduleName, const char *submoduleType) const override{};
  cProperties *getConnectionProperties(int connectionId, const char *channelType) const override{};
  std::string getPackageProperty(const char *name) const override{};
  const char *getImplementationClassName() const override{};
  std::string getCxxNamespace() const override{};
  const char *getSourceFileName() const override{};
  bool isInnerType() const override{};

  TestModuleType(const char *name) : cModuleType(name) {
    cfg = new Configuration;
    props = new cProperties;
  }

  std::string str() const override { return "test module type"; };
  std::string getNedSource() const override { return ""; };
  bool isNetwork() const override { return false; };
  bool isSimple() const override { return true; };
};
}  // namespace quisp_test