#pragma once
#include <omnetpp/simtime_t.h>
#include <functional>
#include <tuple>
#include "omnetpp/simtime.h"

namespace quisp::backends::abstract {

using omnetpp::SimTime;
using omnetpp::SimTimeUnit;
template <typename QubitId>
class IQubit;

template <typename QubitId>
class IQuantumBackend {
 public:
  IQuantumBackend(){};
  virtual ~IQuantumBackend(){};

  virtual IQubit<QubitId>* getQubit(QubitId id) = 0;
  virtual const SimTime& getSimTime() = 0;
  virtual void setSimTime(SimTime time) = 0;

 protected:
};

template <typename QubitId>
class IQubit {
 public:
  IQubit(){};
  virtual ~IQubit(){};

  // // single qubit operations
  // virtual void gateX() = 0;
  // virtual void gateY() = 0;
  // virtual void gateZ() = 0;
  // virtual void gateI() = 0;
  // virtual void gateH() = 0;
  // virtual void gateT() = 0;
  // virtual void gateS() = 0;
  // virtual void gateRx() = 0;
  // virtual void gateRy() = 0;
  // virtual void gateRz() = 0;

  // // two qubit operations
  // virtual void gateCNOT(IQubit const* target) = 0;
  // virtual void gateCZ(IQubit const* anoter) = 0;
  // virtual void gateSWAP() = 0;
};
}  // namespace quisp::backends::abstract

namespace std {
namespace {
// https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
void hash_combine(std::size_t& seed, int const& v) { seed ^= std::hash<int>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2); }

}  // namespace
template <>
struct hash<std::tuple<int, int, int, int>> {
  size_t operator()(const std::tuple<int, int, int, int>& x) const {
    size_t seed = std::hash<int>()(std::get<0>(x));
    hash_combine(seed, std::get<1>(x));
    hash_combine(seed, std::get<2>(x));
    hash_combine(seed, std::get<3>(x));
    return seed;
  }
};
}  // namespace std
