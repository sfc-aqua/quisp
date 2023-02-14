#pragma once
#include <modules/QNIC.h>
#include <nlohmann/json.hpp>

using quisp::modules::QNIC_type;
using json = nlohmann::json;

namespace quisp::rules {

class Clause {
 public:
  Clause() {}
  Clause(int partner_addr) : partner_address(partner_addr){};
  virtual ~Clause(){};
  std::string name = "";
  int partner_address;
  virtual json serialize_json() = 0;
  virtual void deserialize_json(json serialized) = 0;
};

class EnoughResourceConditionClause : public Clause {
 public:
  EnoughResourceConditionClause(json serialized) { deserialize_json(serialized); }
  EnoughResourceConditionClause(int num_resources, int partner_addr);
  const std::string name = "enough_resource";
  int num_resource;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class MeasureCountConditionClause : public Clause {
 public:
  MeasureCountConditionClause(json serialized) { deserialize_json(serialized); }
  MeasureCountConditionClause(int num_measure, int partner_addr);
  const std::string name = "measure_count";
  int num_measure;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class FidelityConditionClause : public Clause {
 public:
  FidelityConditionClause(json serialized) { deserialize_json(serialized); }
  FidelityConditionClause(double required_fidelity, int partner_addr);
  const std::string name = "fidelity";
  double required_fidelity;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class WaitConditionClause : public Clause {
 public:
  WaitConditionClause(json serialized) { deserialize_json(serialized); }
  WaitConditionClause(int swapper_addr);
  const std::string name = "wait";
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

}  // namespace quisp::rules
