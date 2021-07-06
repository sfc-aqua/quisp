#pragma once
#include <omnetpp.h>

namespace quisp_test {
namespace rng {
/**
 * fake randome number generator for unit test
 */
class TestRNG : public omnetpp::cRNG {
 public:
  void initialize(int seedSet, int rngId, int numRngs, int parsimProcId, int parsimNumPartitions, omnetpp::cConfiguration *cfg) override {}
  void selfTest() override {}
  unsigned long intRandMax() override { return 10000; };

  // Random integer in [0,n), n < intRandMax()
  unsigned long intRand(unsigned long n) override { return intValue; };
  unsigned long intRand() override { return intValue; }

  // Random double on the [0,1) interval
  double doubleRand() override { return doubleValue; };

  // Random double on the (0,1) interval
  double doubleRandNonz() override { return doubleValue; };

  // Random double on the [0,1] interval
  double doubleRandIncl1() override { return doubleValue; };

  // Random double on the (0,1] interval
  double doubleRandNonzIncl1() { return 1 - doubleRand(); }
  unsigned long intValue = 0;
  double doubleValue = .0;
};
}  // namespace rng
}  // namespace quisp_test
