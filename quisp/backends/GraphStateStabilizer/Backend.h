#pragma once
#include <unordered_map>
#include "../interfaces/IConfiguration.h"
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "../interfaces/IRandomNumberGenerator.h"
#include "Qubit.h"
#include "omnetpp/simtime.h"

namespace quisp::backends::graph_state_stabilizer {
using abstract::IConfiguration;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::IRandomNumberGenerator;
using omnetpp::SimTime;

class GraphStateStabilizerQubit;

class GraphStateStabilizerBackend : public IQuantumBackend {
 public:
  GraphStateStabilizerBackend(std::unique_ptr<IRandomNumberGenerator> rng);
  ~GraphStateStabilizerBackend();

  IQubit* getQubit(const IQubitId* id) override;
  IQubit* getQubit(const IQubitId* id, std::unique_ptr<IConfiguration> configuration){};
  std::unique_ptr<IConfiguration> getDefaultConfiguration() const {};
  const SimTime& getSimTime(){};
  void setSimTime(SimTime time){};
  double dblrand();

 protected:
  std::unordered_map<const IQubitId*, std::unique_ptr<GraphStateStabilizerQubit>, IQubitId::Hash, IQubitId::Pred> qubits;
  const std::unique_ptr<IRandomNumberGenerator> rng;
};
}  // namespace quisp::backends::graph_state_stabilizer
