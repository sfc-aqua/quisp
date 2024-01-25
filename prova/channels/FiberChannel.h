/** \file QuantumChannel.cc
 *
 *  \brief QuantumChannel
 */
#include <omnetpp.h>
#include <stdexcept>

using namespace omnetpp;

namespace quisp::channels {


class FiberChannel : public cDatarateChannel {
 public:
  FiberChannel();
  void initialize();
  cChannel::Result processMessage(cMessage *msg, const SendOptions &options, simtime_t t);
 protected:

 private:
};

Define_Channel(FiberChannel);

}  // namespace quisp::channels
