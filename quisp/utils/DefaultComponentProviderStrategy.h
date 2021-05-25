#ifndef QUISP_UTILS_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_
#define QUISP_UTILS_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_

#include "utils/IComponentProviderStrategy.h"
#include "utils/utils.h"

namespace quisp {
namespace utils {

class DefaultComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  DefaultComponentProviderStrategy(cModule *_self);
  cModule *getQNode() override;
  StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override;

 private:
  const cModuleType *const QNodeType = cModuleType::get("modules.QNode");
  cModule *self;
};

}  // namespace utils
}  // namespace quisp
#endif
