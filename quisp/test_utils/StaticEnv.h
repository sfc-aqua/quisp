#pragma once

#include <omnetpp.h>
#include "Configuration.h"
#include "omnetpp/ccanvas.h"

namespace quisp_test {
namespace env {

using namespace omnetpp;

/**
 * \brief cEnvir implementation for unit testing based on OMNeT++'s StaticEnv.
 * \see https://github.com/omnetpp/omnetpp/blob/308b3b2b4c060b165911237a9bd9470ea010d34c/src/sim/csimulation.cc#L728
 */
class StaticEnv : public omnetpp::cEnvir {
 protected:
  void unsupported() const { throw std::runtime_error("StaticEnv: Unsupported method called"); }
  void alert(const char *msg) override { ::printf("\n<!> %s\n\n", msg); }
  bool askYesNo(const char *msg) override {
    unsupported();
    return false;
  }

 public:
  StaticEnv();
  ~StaticEnv() {}

  // eventlog callback interface
  void objectDeleted(cObject *object) override {}
  void simulationEvent(cEvent *event) override {}
  void messageScheduled(cMessage *msg) override {}
  void messageCancelled(cMessage *msg) override {}
  void beginSend(cMessage *msg, const omnetpp::SendOptions &options) override {}
  void messageSendDirect(cMessage *msg, cGate *toGate, const omnetpp::ChannelResult &result) override {}
  void messageSendHop(cMessage *msg, cGate *srcGate) override {}
  void messageSendHop(cMessage *msg, cGate *srcGate, const omnetpp::ChannelResult &result) override {}
  void endSend(cMessage *msg) override {}
  void messageCreated(cMessage *msg) override {}
  void messageCloned(cMessage *msg, cMessage *clone) override {}
  void messageDeleted(cMessage *msg) override {}
  void moduleReparented(cModule *module, cModule *oldparent, int oldId) override {}
  void componentMethodBegin(cComponent *from, cComponent *to, const char *methodFmt, va_list va, bool silent) override {}
  void componentMethodEnd() override {}
  void moduleCreated(cModule *newmodule) override {}
  void moduleDeleted(cModule *module) override {}
  void gateCreated(cGate *newgate) override {}
  void gateDeleted(cGate *gate) override {}
  void connectionCreated(cGate *srcgate) override {}
  void connectionDeleted(cGate *srcgate) override {}
  void displayStringChanged(cComponent *component) override {}
  void undisposedObject(cObject *obj) override;
  void log(cLogEntry *entry) override {}

  // configuration, model parameters
  void preconfigure(cComponent *component) override {}
  void configure(cComponent *component) override {}
  void readParameter(cPar *parameter) override { unsupported(); }
  bool isModuleLocal(cModule *parentmod, const char *modname, int index) override { return true; }
  cXMLElement *getXMLDocument(const char *filename, const char *xpath = nullptr) override {
    unsupported();
    return nullptr;
  }
  cXMLElement *getParsedXMLString(const char *content, const char *xpath = nullptr) override {
    unsupported();
    return nullptr;
  }
  void forgetXMLDocument(const char *filename) override {}
  void forgetParsedXMLString(const char *content) override {}
  void flushXMLDocumentCache() override {}
  void flushXMLParsedContentCache() override {}
  unsigned getExtraStackForEnvir() const override { return 0; }
  cConfiguration *getConfig() override;
  std::string resolveResourcePath(const char *fileName, cComponentType *context) override { return ""; }
  bool isGUI() const override { return false; }
  bool isExpressMode() const override { return false; }

  // UI functions (see also protected ones)
  void bubble(cComponent *component, const char *text) override {}
  std::string gets(const char *prompt, const char *defaultreply = nullptr) override;
  cEnvir &flush() {
    ::fflush(stdout);
    return *this;
  }

  // RNGs
  int getNumRNGs() const override { return 0; }
  cRNG *getRNG(int k) override;

  // output vectors
  void *registerOutputVector(const char *modulename, const char *vectorname) override { return nullptr; }
  void deregisterOutputVector(void *vechandle) override {}
  void setVectorAttribute(void *vechandle, const char *name, const char *value) override {}
  bool recordInOutputVector(void *vechandle, simtime_t t, double value) override { return false; }

  // output scalars
  void recordScalar(cComponent *component, const char *name, double value, opp_string_map *attributes = nullptr) override {}
  void recordStatistic(cComponent *component, const char *name, cStatistic *statistic, opp_string_map *attributes = nullptr) override {}

  void addResultRecorders(cComponent *component, simsignal_t signal, const char *statisticName, cProperty *statisticTemplateProperty) override {}

  // snapshot file
  virtual std::ostream *getStreamForSnapshot() override {
    unsupported();
    return nullptr;
  }
  void releaseStreamForSnapshot(std::ostream *os) override { unsupported(); }

  // misc
  int getArgCount() const override {
    unsupported();
    return 0;
  }
  char **getArgVector() const override {
    unsupported();
    return nullptr;
  }
  int getParsimProcId() const override { return 0; }
  int getParsimNumPartitions() const override { return 1; }
  unsigned long getUniqueNumber() override {
    unsupported();
    return 0;
  }
  bool idle() override { return false; }
  void refOsgNode(osg::Node *scene) override {}
  void unrefOsgNode(osg::Node *scene) override {}
  bool ensureDebugger(cRuntimeError *) override { return false; }

  void getImageSize(const char *imageName, double &outWidth, double &outHeight) override { unsupported(); }
  void getTextExtent(const cFigure::Font &font, const char *text, double &outWidth, double &outHeight, double &outAscent) override { unsupported(); }
  void appendToImagePath(const char *directory) override { unsupported(); }
  void loadImage(const char *fileName, const char *imageName = nullptr) override { unsupported(); }
  cFigure::Rectangle getSubmoduleBounds(const cModule *submodule) override { return cFigure::Rectangle(NAN, NAN, NAN, NAN); }
  double getZoomLevel(const cModule *module) override { return NAN; }
  double getAnimationTime() const override { return 0; }
  double getAnimationSpeed() const override { return 0; }
  double getRemainingAnimationHoldTime() const override { return 0; }

  // lifecycle listeners
  void addLifecycleListener(cISimulationLifecycleListener *listener) override {}
  void removeLifecycleListener(cISimulationLifecycleListener *listener) override {}
  void notifyLifecycleListeners(SimulationLifecycleEventType eventType, cObject *details) override {}

  std::vector<cFigure::Point> getConnectionLine(const cGate *sourceGate) override { return std::vector<cFigure::Point>(); }
  void recordParameter(cPar *par) override {}
  void recordComponentType(cComponent *component) override {}

  cSimulation *newSimulation();
  void resetSimulation();
  cRNG *rng = nullptr;
};

}  // namespace env
}  // namespace quisp_test
