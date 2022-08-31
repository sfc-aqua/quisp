
#include <modules/QNIC.h>

namespace quisp::rules::active::actions::base {
class FreeResource {
  void run(QNIC_type qnic_type, int qnic_id, int qubit_id);
};
}  // namespace quisp::rules::active::actions::base