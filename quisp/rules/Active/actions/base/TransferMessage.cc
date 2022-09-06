#include <messages/classical_messages.h>

namespace quisp::rules::active::actions::base {
using namespace messages;

static PurificationResult* generatePurificationResult(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind, bool is_output_plus) {
  PurificationResult* pk = new PurificationResult;
  pk->setDestAddr(partner);
  pk->setKind(kind);
  pk->setAction_index(action_index);
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setShared_tag(shared_tag);
  pk->setOutput_is_plus(is_output_plus);
  return pk;
}
static DoublePurificationResult* generateDoublePurificationResult(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind,
                                                                  bool is_x_output_plus, bool is_z_output_plus) {
  DoublePurificationResult* pk = new DoublePurificationResult;
  pk->setDestAddr(partner);
  pk->setKind(kind);
  pk->setAction_index(action_index);
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setShared_tag(shared_tag);
  pk->setXOutput_is_plus(is_x_output_plus);
  pk->setZOutput_is_plus(is_z_output_plus);
  return pk;
}

static DS_DoublePurificationResult* generateDoubleSelectionDoublePurificationResult(int partner, unsigned long ruleset_id, int rule_id, int shared_tag, int action_index, int kind,
                                                                                    bool is_x_output_plus, bool is_z_output_plus, bool is_ds_x_output_plus,
                                                                                    bool is_ds_z_output_plus) {
  DS_DoublePurificationResult* pk = new DS_DoublePurificationResult;
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
  return pk;
}

static DS_DoublePurificationSecondResult* generateDoubleSelectionDoublePurificationSecondResult(int partner, unsigned long ruleset_id, int rule_id, int shared_tag,
                                                                                                int action_index, int kind, bool is_x_output_plus, bool is_z_output_plus,
                                                                                                bool is_ds_output_plus) {
  DS_DoublePurificationSecondResult* pk = new DS_DoublePurificationSecondResult;
  pk->setDestAddr(partner);
  pk->setKind(kind);
  pk->setAction_index(action_index);
  pk->setRule_id(rule_id);
  pk->setRuleset_id(ruleset_id);
  pk->setShared_tag(shared_tag);
  pk->setXOutput_is_plus(is_x_output_plus);
  pk->setZOutput_is_plus(is_z_output_plus);
  pk->setDS_Output_is_plus(is_ds_output_plus);
  return pk;
}

}  // namespace quisp::rules::active::actions::base