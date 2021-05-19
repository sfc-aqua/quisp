#ifndef QUISP_MODULES_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_
#define QUISP_MODULES_DEFAULT_COMPONENT_PROVIDER_STRATEGY_H_
#include "IComponentProviderStrategy.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "omnetpp.h"

using omnetpp::cModule;

namespace quisp {
namespace modules {

class DefaultComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  DefaultComponentProviderStrategy(cModule *_self);
  cModule *getQNode() override;
  StationaryQubit *getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override;

 private:
  const cModuleType *const QNodeType = cModuleType::get("modules.QNode");
  cModule *self;
};

}  // namespace modules
}  // namespace quisp
#endif
