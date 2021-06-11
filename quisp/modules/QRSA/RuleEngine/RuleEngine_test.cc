#include "RuleEngine.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "modules/QRSA/RuleEngine/RuleEngine.h"
#include "omnetpp/csimulation.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;

class MockStationaryQubit : public StationaryQubit {
 public:
  MOCK_METHOD(void, emitPhoton, (int pulse), (override));
  MOCK_METHOD(void, setFree, (bool consumed), (override));
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr) {}
  Strategy(MockStationaryQubit* _qubit) : mockQubit(_qubit) {}
  ~Strategy() { delete mockQubit; }
  MockStationaryQubit* mockQubit = nullptr;
  StationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockStationaryQubit();
    return mockQubit;
  };
};

class RuleEngineTestTarget : public quisp::modules::RuleEngine {
 public:
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
  RuleEngineTestTarget(MockStationaryQubit* mockQubit) : quisp::modules::RuleEngine() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 0);
    setParInt(this, "number_of_qnics", 0);
    setParInt(this, "total_number_of_qnics", 0);
    // setParBool(this, "link_tomography", false);
    // setParStr(this, "tomography_output_filename", "test_file");
    // setParStr(this, "file_dir_name", "out/tests");
    // setParInt(this, "initial_purification", 0);
    // setParBool(this, "X_purification", true);
    // setParBool(this, "Z_purification", true);
    // setParInt(this, "Purification_type", 0);
    // setParInt(this, "num_measure", 0);

    this->setName("rule_engine_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>(mockQubit));
  }
};

TEST(RuleEngineTest, Init) {
  RuleEngineTestTarget c{nullptr};
  c.initialize();
  ASSERT_EQ(c.par("address").intValue(), 123);
}

}  // namespace
