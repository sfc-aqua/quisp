#include <gtest/gtest.h>
#include <omnetpp.h>
#include <nlohmann/json.hpp>

#include "ConnectionManager.h"
#include "RuleSetGenerator.h"

using json = nlohmann::json;
using OriginalRSG = quisp::modules::ruleset_gen::RuleSetGenerator;
namespace {
class RuleSetGenerator : OriginalRSG {
 public:
  RuleSetGenerator(int responder_addr) : OriginalRSG(responder_addr) {}
  using OriginalRSG::collectPath;
  using OriginalRSG::collectSwappingPartners;
  using OriginalRSG::fillPathDivision;
  using OriginalRSG::purifyRule;
  using OriginalRSG::swapRule;
  using OriginalRSG::tomographyRule;
  using OriginalRSG::waitRule;
};
TEST(RuleSetGenerator, Simple) {
  int responder_addr = 7;
  RuleSetGenerator rsg{responder_addr};
}
}  // namespace
