#pragma once
#include <backends/Backends.h>
#include <omnetpp.h>
#include <memory>
#include <stdexcept>
#include "../interfaces/IQubitId.h"
#include "../interfaces/IRandomNumberGenerator.h"
#include "Backend.h"
#include "Configuration.h"
#include "Qubit.h"

namespace quisp_test::backends::error_tracking {
using omnetpp::SimTime;
using ::quisp::backends::abstract::IQubit;
using ::quisp::backends::abstract::IQubitId;
using ::quisp::backends::error_tracking::ErrorTrackingBackend;
using ::quisp::backends::error_tracking::ErrorTrackingConfiguration;
using ::quisp::backends::error_tracking::ErrorTrackingQubit;
using namespace ::quisp::backends;
using namespace ::quisp::backends::abstract;
using Complex = std::complex<double>;

class QubitId : public IQubitId {
 public:
  QubitId(int id) : id(id) {}
  int id;

  inline std::size_t hash() const override { return std::hash<int>()(id); }
  bool compare(const IQubitId& qubit_id_ref) const override {
    auto qubit_id = dynamic_cast<const QubitId&>(qubit_id_ref);
    return id == qubit_id.id;
  }
};

class TestRNG : public quisp::backends::abstract::IRandomNumberGenerator {
 public:
  TestRNG() {}
  double doubleRandom() override { return double_value; }
  double double_value = 0.0;
};

class Qubit : public ErrorTrackingQubit {
 public:
  using ErrorTrackingQubit::addErrorX;
  using ErrorTrackingQubit::addErrorZ;
  using ErrorTrackingQubit::applyMemoryError;
  using ErrorTrackingQubit::applySingleQubitGateError;
  using ErrorTrackingQubit::applyTwoQubitGateError;
  using ErrorTrackingQubit::correlationMeasureX;
  using ErrorTrackingQubit::correlationMeasureY;
  using ErrorTrackingQubit::correlationMeasureZ;
  using ErrorTrackingQubit::entangled_partner;
  using ErrorTrackingQubit::gate_err_cnot;
  using ErrorTrackingQubit::gate_err_h;
  using ErrorTrackingQubit::gate_err_x;
  using ErrorTrackingQubit::gate_err_z;
  using ErrorTrackingQubit::getErrorMatrix;
  using ErrorTrackingQubit::getQuantumState;
  using ErrorTrackingQubit::has_completely_mixed_error;
  using ErrorTrackingQubit::has_excitation_error;
  using ErrorTrackingQubit::has_relaxation_error;
  using ErrorTrackingQubit::has_x_error;
  using ErrorTrackingQubit::has_z_error;
  using ErrorTrackingQubit::localMeasureX;
  using ErrorTrackingQubit::localMeasureZ;
  using ErrorTrackingQubit::measureDensityIndependent;
  using ErrorTrackingQubit::measurement_err;
  using ErrorTrackingQubit::memory_transition_matrix;
  using ErrorTrackingQubit::setMemoryErrorRates;
  using ErrorTrackingQubit::updated_time;

  Qubit(const IQubitId* id, ErrorTrackingBackend* const backend) : ErrorTrackingQubit(id, backend) {}
  void reset() {
    setFree();
    updated_time = SimTime(0);
    no_density_matrix_nullptr_entangled_partner_ok = true;
  }
};

class Backend : public ErrorTrackingBackend {
 public:
  using ErrorTrackingBackend::qubits;
  Backend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<ErrorTrackingConfiguration> config) : ErrorTrackingBackend(std::move(rng), std::move(config)) {}
  IQubit* getQubit(int id) { return this->getQubitInternal(new QubitId(id)); }
  IQubit* getQubitInternal(const IQubitId* id) {
    auto qubit = qubits.find(id);

    if (qubit != qubits.cend()) {
      return qubit->second.get();
    }
    auto original_qubit = std::make_unique<Qubit>(id, this);
    auto* qubit_ptr = original_qubit.get();
    qubits.insert({id, std::move(original_qubit)});
    return qubit_ptr;
  }
};

}  // namespace quisp_test::backends::error_tracking
