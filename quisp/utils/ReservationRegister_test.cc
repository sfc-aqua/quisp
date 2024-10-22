#include "ReservationRegister.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>

#include "messages/classical_messages.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace omnetpp;
using namespace quisp_test;
using namespace testing;
using namespace quisp::messages;
using quisp::utils::ReservationRegister;

class ReservationRegisterTest : public ::testing::Test {
 protected:
  void SetUp() { register_under_test = new ReservationRegister(); }
  ReservationRegister* register_under_test;
};

TEST_F(ReservationRegisterTest, QnicReservation) {
  int qnic_address = 13, qnic_address2 = 15;
  unsigned long ruleset_id = 12345;
  // qnic reservation
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 0);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 0);
  register_under_test->registerReservation(qnic_address, ruleset_id);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMap().find(qnic_address)->second, ruleset_id);
  EXPECT_EQ(*(register_under_test->getRsidToQnicAddrMap()
                  .find(ruleset_id)  // found a (ruleset id - qnic set) pair
                  ->second  // access the qnic set
                  .begin())  // take the first element
            ,
            qnic_address);
  EXPECT_TRUE(register_under_test->isQnicBusy(qnic_address));
  EXPECT_FALSE(register_under_test->isQnicBusy(qnic_address2));
}

TEST_F(ReservationRegisterTest, SameRuleSetSeveralQnics) {
  int qnic_address = 13, qnic_address2 = 15;
  unsigned long ruleset_id = 12345;
  // qnic reservation
  register_under_test->registerReservation(qnic_address, ruleset_id);
  register_under_test->registerReservation(qnic_address2, ruleset_id);
  EXPECT_TRUE(register_under_test->isQnicBusy(qnic_address));
  EXPECT_TRUE(register_under_test->isQnicBusy(qnic_address2));
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 2);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMap().find(qnic_address)->second, ruleset_id);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMap().find(qnic_address2)->second, ruleset_id);

  EXPECT_EQ(*(register_under_test->getRsidToQnicAddrMap()
                  .find(ruleset_id)  // found a (ruleset id - qnic set) pair
                  ->second  // access the qnic set
                  .begin())  // take the first element
            ,
            qnic_address);

  EXPECT_EQ(*++(register_under_test->getRsidToQnicAddrMap()
                    .find(ruleset_id)  // found a (ruleset id - qnic set) pair
                    ->second  // access the qnic set
                    .begin())  // take the first element
            ,
            qnic_address2);
}

TEST_F(ReservationRegisterTest, ReleaseReservationsByQnicAddr) {
  int qnic_address = 13, qnic_address2 = 15;
  unsigned long ruleset_id = 12345;
  // qnic reservation
  register_under_test->registerReservation(qnic_address, ruleset_id);
  register_under_test->registerReservation(qnic_address2, ruleset_id);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 2);
  register_under_test->deleteReservationByQnicAddr(qnic_address);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 1);
  EXPECT_EQ(*(register_under_test->getRsidToQnicAddrMap()
                  .find(ruleset_id)  // found a (ruleset id - qnic set) pair
                  ->second  // access the qnic set
                  .begin())  // take the first element
            ,
            qnic_address2);
  register_under_test->deleteReservationByQnicAddr(qnic_address2);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 0);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 0);
}

TEST_F(ReservationRegisterTest, ReleaseReservationsByRulesetId) {
  int qnic_address = 13, qnic_address2 = 15;
  unsigned long ruleset_id = 12345;
  // qnic reservation
  register_under_test->registerReservation(qnic_address, ruleset_id);
  register_under_test->registerReservation(qnic_address2, ruleset_id);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 2);
  register_under_test->deleteReservationByRulesetId(ruleset_id);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 0);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 0);
}

TEST_F(ReservationRegisterTest, UpdateRulesetId) {
  int qnic_address = 13, qnic_address2 = 15;
  unsigned long ruleset_id = 12345, ruleset_id2 = 54321;
  // qnic reservation
  register_under_test->registerReservation(qnic_address, ruleset_id);
  register_under_test->registerReservation(qnic_address2, ruleset_id);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 2);
  register_under_test->updateReservationId(ruleset_id, ruleset_id2);
  EXPECT_EQ(register_under_test->getRsidToQnicAddrMapSize(), 1);
  EXPECT_EQ(register_under_test->getQnicAddrToRsidMapSize(), 2);
  EXPECT_EQ(*(register_under_test->getRsidToQnicAddrMap()
                  .find(ruleset_id2)  // found a (ruleset id - qnic set) pair
                  ->second  // access the qnic set
                  .begin())  // take the first element
            ,
            qnic_address);
  EXPECT_EQ(*++(register_under_test->getRsidToQnicAddrMap()
                    .find(ruleset_id2)  // found a (ruleset id - qnic set) pair
                    ->second  // access the qnic set
                    .begin())  // take the first element
            ,
            qnic_address2);
}

}  // namespace
