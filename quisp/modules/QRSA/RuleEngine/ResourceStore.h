#pragma once

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
namespace quisp {
namespace modules {
class ResourceStore {
 public:
  ResourceStore();
  ~ResourceStore();
  void erase(QNIC_type qnic_type, int qnic_index, StationaryQubit* const qubit);
  void insert(QNIC_type qnic_type, int qnic_index, int addr, StationaryQubit* const qubit);
  StationaryQubit* find(QNIC_type qnic_type, int qnic_index, int addr);
  std::multimap<int, quisp::modules::StationaryQubit*> range(QNIC_type qnic_type, int qnic_index);

 protected:
  std::map<std::pair<QNIC_type, int>, std::multimap<int, quisp::modules::StationaryQubit*>> _resources;
};
}  // namespace modules
}  // namespace quisp
