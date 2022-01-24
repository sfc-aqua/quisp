#pragma once

#include <modules/QNIC.h>

namespace quisp::rules {

class BaseClause {
 public:
  modules::QNIC_type qnic_type;
  int qnic_id;
};

class EnoughResourceConditionClause : public BaseClause {
 public:
  EnoughResourceConditionClause(int num_resources, int partner_address, double required_fidelity);
  int num_resource;
  int partner_addr;
  double required_fidelity;
};

class MeasureCountConditionClause : public BaseClause {
 public:
  MeasureCountConditionClause(int num_measure);
  int num_measure;
};

}  // namespace quisp::rules
