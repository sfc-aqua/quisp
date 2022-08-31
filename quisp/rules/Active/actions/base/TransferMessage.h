
#include <messages/classical_messages.h>
#include <modules/QNIC.h>
#include "BaseAction.h"
namespace quisp::rules::active::actions::base {

class TransferMessage : public BaseAction {
 public:
  // Constructor for Purification Result
  TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_output_plus);
  // Constructor for Double Purification Result
  TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_x_output_plus, bool is_z_output_plus);
  // Constructor for Double Purification Second Result
  TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_x_output_plus, bool is_z_output_plus,
                  bool is_output_plus);
  // Constructor for Double Selection Double Purification Result
  TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_x_output_plus, bool is_z_output_plus,
                  bool is_ds_x_output_plus, bool is_ds_z_output_plus);
  cPacket* message;
  cPacket* generate() { return message; };
};
}  // namespace quisp::rules::active::actions::base