#pragma once
#include <modules/QNIC.h>
#include <nlohmann/json.hpp>

using quisp::modules::QNIC_type;
using json = nlohmann::json;

namespace quisp::rules {

class Clause {
 public:
  Clause(int partner_addr, QNIC_type qnic_type, int qnic_id) : partner_address(partner_addr), qnic_type(qnic_type), qnic_id(qnic_id){};
  virtual ~Clause(){};
  std::string name = "";
  int partner_address;
  QNIC_type qnic_type;
  int qnic_id;
  virtual json serialize_json() = 0;
  virtual std::string getName() = 0;
};

class EnoughResourceConditionClause : public Clause {
 public:
  EnoughResourceConditionClause(int num_resources, double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id);
  std::string name = "enough_resource";
  int num_resource;
  double required_fidelity;
  json serialize_json() override;
  std::string getName() override { return name; };
};

class MeasureCountConditionClause : public Clause {
 public:
  MeasureCountConditionClause(int num_measure, int partner_addr, QNIC_type qnic_type, int qnic_id);
  std::string name = "measure_count";
  int num_measure;
  json serialize_json() override;
  std::string getName() override { return name; };
};

class FidelityConditionClause : public Clause {
 public:
  FidelityConditionClause(double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id);
  std::string name = "fidelity";
  double required_fidelity;
  json serialize_json() override;
  std::string getName() override { return name; };
};

class WaitConditionClause : public Clause {
 public:
  WaitConditionClause(int partner_addr, QNIC_type qnic_type, int qnic_id);
  std::string name = "wait";
  json serialize_json() override;
  std::string getName() override { return name; };
};

}  // namespace quisp::rules
