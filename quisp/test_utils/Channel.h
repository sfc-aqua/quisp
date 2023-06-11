#pragma once

#include <omnetpp.h>
#include <cstddef>
#include <optional>
#include "omnetpp/cchannel.h"
#include "omnetpp/cdataratechannel.h"
#include "omnetpp/simtime_t.h"

namespace quisp_test {
namespace channel {

using omnetpp::cMessage;
using omnetpp::cModule;
using omnetpp::SendOptions;
using omnetpp::simtime_t;
using omnetpp::internal::cDoubleParImpl;
using omnetpp::internal::cParImpl;

class TestDatarateChannel : public omnetpp::cDatarateChannel {
 public:
  explicit TestDatarateChannel();

  void setCost(double cost = 1);
};
}  // namespace channel
}  // namespace quisp_test
