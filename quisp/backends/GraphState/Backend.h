#pragma once
#include <omnetpp.h>
#include <memory>
#include <unordered_map>
#include "../interfaces/IConfiguration.h"
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "../interfaces/IRandomNumberGenerator.h"
#include "Configuration.h"
#include "Qubit.h"

namespace quisp::backends::graph_state {
using abstract::IConfiguration;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::IRandomNumberGenerator;
using graph_state::GraphStateQubit;
using omnetpp::SimTime;

class GraphStateBackend : public IQuantumBackend {
 public:
  class ICallback {
   public:
    virtual ~ICallback() {}
    virtual void willUpdate(GraphStateBackend& backend) = 0;
  };
  GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateConfiguration> configuration);
  GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<GraphStateConfiguration> configuration, ICallback* callback);
  ~GraphStateBackend();
  IQubit* getQubit(const IQubitId* id) override;
  IQubit* getQubit(const IQubitId* id, std::unique_ptr<IConfiguration> configuration) override;
  std::unique_ptr<IConfiguration> getDefaultConfiguration() const override;
  const SimTime& getSimTime() override;
  void setSimTime(SimTime time) override;
  double dblrand();

 protected:
  std::unordered_map<const IQubitId*, std::unique_ptr<GraphStateQubit>, IQubitId::Hash, IQubitId::Pred> qubits;
  SimTime current_time;
  const std::unique_ptr<IRandomNumberGenerator> rng;
  std::unique_ptr<GraphStateConfiguration> config;
  ICallback* callback = nullptr;
};
}  // namespace quisp::backends::graph_state
