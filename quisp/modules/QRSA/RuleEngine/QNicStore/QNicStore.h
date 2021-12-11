#pragma once
#include <memory>
#include <vector>
#include "../QNicRecord/IQNicRecord.h"
#include "../QNicRecord/QNicRecord.h"
#include "IQNicStore.h"
#include "utils/ComponentProvider.h"
namespace quisp::modules::qnic_store {

using UniqueQNicRecord = std::unique_ptr<quisp::modules::qnic_record::IQNicRecord>;
using QNicRecordType = quisp::modules::qnic_record::QNicRecord;

using QNicIndex = int;
class QNicStore : public IQNicStore {
 public:
  QNicStore(utils::ComponentProvider& provider, int number_of_emitter_qnics, int number_of_receiver_qnics, int number_of_passive_receiver_qnics);
  ~QNicStore(){};

 protected:
  std::map<QNIC_type, std::vector<UniqueQNicRecord>> qnics;

  utils::ComponentProvider& provider;
};
}  // namespace quisp::modules::qnic_store
