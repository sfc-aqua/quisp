#include "QNicStore.h"
#include <array>
#include "modules/QNIC.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::qnic_store {

using utils::ComponentProvider;

QNicStore::QNicStore(ComponentProvider& provider, int number_of_emitter_qnics, int number_of_receiver_qnics, int number_of_passive_receiver_qnics) : provider(provider) {
  std::array<std::pair<QNIC_type, int /* number of qnics */>, 3 /* the number of kinds of QNICs */> qnic_details = {
      {{QNIC_E, number_of_emitter_qnics}, {QNIC_R, number_of_receiver_qnics}, {QNIC_RP, number_of_passive_receiver_qnics}}};

  for (auto& [type, num_qnics] : qnic_details) {
    qnics.insert(std::make_pair(type, std::vector<UniqueQNicRecord>()));
    auto qnic_vec = &qnics.at(type);
    for (int i = 0; i < num_qnics; i++) {
      cModule* qnic = provider.getQNIC(i, type);
      if (qnic == nullptr) {
        throw cRuntimeError("QNicStore::QNicStore(): %s QNIC with index %d not found", QNIC_names[type], i);
      }
      qnic_vec->emplace_back(std::make_unique<QNicRecordType>(provider, i, type));
    }
  }
}

int QNicStore::countNumFreeQubits(QNIC_type type, int qnic_index) {
  auto& qnic = getQNic(type, qnic_index);
  return qnic->countNumFreeQubits();
}

int QNicStore::takeFreeQubitIndex(QNIC_type type, int qnic_index) {
  auto& qnic = getQNic(type, qnic_index);
  return qnic->takeFreeQubitIndex();
}

void QNicStore::setQubitBusy(QNIC_type type, int qnic_index, int qubit_index, bool is_busy) {
  auto& qnic = getQNic(type, qnic_index);
  return qnic->setQubitBusy(qubit_index, is_busy);
}

UniqueQNicRecord& QNicStore::getQNic(QNIC_type type, int qnic_index) {
  if (qnics.size() <= type) {
    throw cRuntimeError("QNicStore::getQNic(): QNIC type %d not found", type);
  }
  auto& qnic_vec = qnics.at(type);
  if (qnic_vec.size() <= qnic_index) {
    throw cRuntimeError("QNicStore::getQNic(): QNIC %s with index %d not found", QNIC_names[type], qnic_index);
  }
  return qnic_vec.at(qnic_index);
}

}  // namespace quisp::modules::qnic_store
