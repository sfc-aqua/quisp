#include "TransferMessage.h"
#include "BaseAction.h"

namespace quisp::rules::active::actions::base {

TransferMessage::TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_output_plus)
    : BaseAction(partner, ruleset_id, rule_id, shared_tag) {
  PurificationResult *pk = new messages::PurificationResult;
  pk->setDestAddr(dst);
  pk->setKind(kind);
  pk->setAction_index(action_index);
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setShared_tag(shared_tag);
  pk->setOutput_is_plus(is_output_plus);
  message = pk;
}

TransferMessage::TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_x_output_plus, bool is_z_output_plus)
    : BaseAction(partner, ruleset_id, rule_id, shared_tag) {
  DoublePurificationResult *pk = new messages::DoublePurificationResult;
  pk->setDestAddr(partner);
  pk->setKind(kind);
  pk->setAction_index(action_index);
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setShared_tag(shared_tag);
  pk->setXOutput_is_plus(is_x_output_plus);
  pk->setZOutput_is_plus(is_z_output_plus);
  message = pk;
}

TransferMessage::TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_x_output_plus, bool is_z_output_plus,
                                 bool is_ds_output_plus)
    : BaseAction(partner, ruleset_id, rule_id, shared_tag) {
  DS_DoublePurificationSecondResult *pk = new DS_DoublePurificationSecondResult;
  pk->setDestAddr(partner);
  pk->setKind(7);
  pk->setAction_index(action_index);
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setShared_tag(shared_tag);
  pk->setXOutput_is_plus(is_x_output_plus);
  pk->setZOutput_is_plus(is_z_output_plus);
  pk->setDS_Output_is_plus(is_ds_output_plus);
  message = pk;
}

TransferMessage::TransferMessage(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_x_output_plus, bool is_z_output_plus,
                                 bool is_ds_x_output_plus, bool is_ds_z_output_plus)
    : BaseAction(partner, ruleset_id, rule_id, shared_tag) {
  DS_DoublePurificationResult *pk = new messages::DS_DoublePurificationResult;
  pk->setDestAddr(partner);
  pk->setKind(kind);
  pk->setAction_index(action_index);
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setShared_tag(shared_tag);
  pk->setXOutput_is_plus(is_x_output_plus);
  pk->setZOutput_is_plus(is_z_output_plus);
  pk->setDS_XOutput_is_plus(is_ds_x_output_plus);
  pk->setDS_ZOutput_is_plus(is_ds_z_output_plus);
  message = pk;
}

}  // namespace quisp::rules::active::actions::base