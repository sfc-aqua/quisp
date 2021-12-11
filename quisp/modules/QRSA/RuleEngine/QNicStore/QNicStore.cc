#include "QNicStore.h"
#include <array>
#include "modules/QNIC.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::qnic_store {

using utils::ComponentProvider;
QNicStore::QNicStore(ComponentProvider& provider, int number_of_emitter_qnics, int number_of_receiver_qnics, int number_of_passive_receiver_qnics) : provider(provider) {
  std::array<QNIC_type, 3> qnic_types = {QNIC_E, QNIC_R, QNIC_RP};

  for (auto& type : qnic_types) {
    qnics.insert(std::make_pair(type, std::vector<UniqueQNicRecord>()));
    auto qnic_vec = &qnics.at(type);
    for (int i = 0; i < number_of_emitter_qnics; i++) {
      cModule* qnic = provider.getQNIC(i, type);
      if (qnic == nullptr) {
        throw cRuntimeError("QNicStore::QNicStore(): %s QNIC with index %d not found", QNIC_names[type], i);
      }
      qnic_vec->emplace_back(std::make_unique<QNicRecordType>(provider, i, type));
    }
  }
}

}  // namespace quisp::modules::qnic_store
