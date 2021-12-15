#include "QubitRecord.h"
#include "gtest/gtest.h"
#include "omnetpp/cexception.h"
#include "omnetpp/cmodule.h"
#include "test_utils/TestUtils.h"
#include "utils/ComponentProvider.h"

namespace {
using namespace quisp_test;
using quisp::utils::ComponentProvider;

class QubitRecord : public quisp::modules::qubit_record::QubitRecord {
 public:
  using quisp::modules::qubit_record::QubitRecord::is_busy;
  using quisp::modules::qubit_record::QubitRecord::qnic_index;
  using quisp::modules::qubit_record::QubitRecord::qnic_type;
  using quisp::modules::qubit_record::QubitRecord::qubit_index;
  QubitRecord(int qnic_index, QNIC_type qnic_type, int qubit_index) : quisp::modules::qubit_record::QubitRecord(qnic_index, qnic_type, qubit_index) {}
};

TEST(QubitRecord, Init) {
  int qnic_index = 3;
  auto qnic_type = QNIC_R;
  int qubit_index = 5;
  QubitRecord record(qnic_index, qnic_type, qubit_index);
  EXPECT_EQ(qubit_index, record.getQubitIndex());
  EXPECT_EQ(qubit_index, record.qubit_index);
  EXPECT_EQ(qnic_index, record.qnic_index);
  EXPECT_EQ(qnic_type, record.qnic_type);
}

TEST(QubitRecord, SetBusy) {
  int qnic_index = 3;
  auto qnic_type = QNIC_R;
  int qubit_index = 5;
  QubitRecord record(qnic_index, qnic_type, qubit_index);
  EXPECT_FALSE(record.is_busy);
  record.setBusy(true);
  EXPECT_TRUE(record.is_busy);
  EXPECT_THROW(record.setBusy(true), omnetpp::cRuntimeError);
}

}  // namespace
