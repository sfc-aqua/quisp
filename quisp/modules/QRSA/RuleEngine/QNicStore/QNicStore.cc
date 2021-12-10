#include "QNicStore.h"
#include "modules/QNIC.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules::qnic_store {

using utils::ComponentProvider;
QNicStore::QNicStore(ComponentProvider& provider, int number_of_emitter_qnics, int number_of_receiver_qnics, int number_of_passive_receiver_qnics) : provider(provider) {
  QNIC_type qnic_type = QNIC_E;
  for (int i = 0; i < number_of_emitter_qnics; i++) {
    cModule* qnic = provider.getQNIC(i, qnic_type);
    if (qnic == nullptr) {
      throw cRuntimeError("QNicStore::QNicStore(): Emitter QNIC with index %d not found", i);
    }
    emitter_qnics.push_back(std::make_unique<QNicRecordType>(i, qnic_type));
  }
  qnic_type = QNIC_R;
  for (int i = 0; i < number_of_receiver_qnics; i++) {
    cModule* qnic = provider.getQNIC(i, qnic_type);
    if (qnic == nullptr) {
      throw cRuntimeError("QNicStore::QNicStore():Receiver QNIC with index %d not found", i);
    }
    receiver_qnics.push_back(std::make_unique<QNicRecordType>(i, qnic_type));
  }
  qnic_type = QNIC_RP;
  for (int i = 0; i < number_of_passive_receiver_qnics; i++) {
    cModule* qnic = provider.getQNIC(i, qnic_type);
    if (qnic == nullptr) {
      throw cRuntimeError("QNicStore::QNicStore(): Passive Receiver QNIC with index %d not found", i);
    }
    passive_receiver_qnics.push_back(std::make_unique<QNicRecordType>(i, qnic_type));
  }
}

}  // namespace quisp::modules::qnic_store
