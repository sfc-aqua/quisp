#pragma once
#include <omnetpp.h>
#include <climits>

namespace quisp_test {
namespace rng {
/**
 * fake randome number generator for unit test
 */
class TestRNG : public omnetpp::cRNG {
 public:
  void initialize(int seedSet, int rngId, int numRngs, int parsimProcId, int parsimNumPartitions, omnetpp::cConfiguration *cfg) override {}
  void selfTest() override {}
  unsigned int intRandMax() override { return UINT_MAX; };

  // Random integer in [0,n), n < intRandMax()
  unsigned int intRand(unsigned int n) override { return intValue; };
  unsigned int intRand() override { return intValue; }

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
