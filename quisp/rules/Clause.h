#pragma once

#include <modules/QNIC.h>

using quisp::modules::QNIC_type;

namespace quisp::rules {

class Clause {
 public:
  Clause(int partner_addr, QNIC_type qnic_type, int qnic_id) : partner_address(partner_addr), qnic_type(qnic_type), qnic_id(qnic_id){};
  int partner_address;
  QNIC_type qnic_type;
  int qnic_id;
};

class EnoughResourceConditionClause : public Clause {
 public:
  EnoughResourceConditionClause(int num_resources, double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id);
  int num_resource;
  double required_fidelity;
};

class MeasureCountConditionClause : public Clause {
 public:
  MeasureCountConditionClause(int num_measure, int partner_addr, QNIC_type qnic_type, int qnic_id);
  int num_measure;
};

class FidelityConditionClause : public Clause {
 public:
  FidelityConditionClause(double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id);
  double required_fidelity;
};

class WaitConditionClause : public Clause {
 public:
  WaitConditionClause(int partner_addr, QNIC_type qnic_type, int qnic_id);
};

}  // namespace quisp::rules
