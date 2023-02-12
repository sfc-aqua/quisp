#pragma once
#include <omnetpp.h>
#include <deque>
#include <memory>
#include <unordered_map>
#include "../interfaces/IConfiguration.h"
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubit.h"
#include "../interfaces/IRandomNumberGenerator.h"
#include "Qubit.h"
#include "backends/QubitConfiguration.h"
#include "backends/interfaces/IQubitId.h"

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
  GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> configuration);
  GraphStateBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<StationaryQubitConfiguration> configuration, ICallback* callback);
  ~GraphStateBackend();
  IQubit* createQubit(const IQubitId* id, std::unique_ptr<IConfiguration> conf) override;
  IQubit* createQubit(const IQubitId* id) override;
  IQubit* createShortLiveQubit() override;
  IQubit* getQubit(const IQubitId* id) override;
  IQubit* getShortLiveQubit() override;
  void returnToPool(IQubit*) override;
  void deleteQubit(const IQubitId* id) override;
  std::unique_ptr<IConfiguration> getDefaultConfiguration() const override;
  const SimTime& getSimTime() override;
  void setSimTime(SimTime time) override;
  double dblrand();

 protected:
  std::unordered_map<const IQubitId*, std::unique_ptr<GraphStateQubit>, IQubitId::Hash, IQubitId::Pred> qubits;
  SimTime current_time;
  const std::unique_ptr<IRandomNumberGenerator> rng;
  std::unique_ptr<StationaryQubitConfiguration> config;
  ICallback* callback = nullptr;
  std::deque<IQubit*> short_live_qubit_pool;
  int short_live_qubit_pool_size;  // this is used to generate qubit id for short live qubits in a pool; currenlty only photons.
};
}  // namespace quisp::backends::graph_state
