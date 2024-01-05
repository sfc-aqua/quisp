#pragma once

namespace quisp::physical::types {

enum class PauliOperator : int { I = 0, X, Y, Z };
enum class BellState : int { PhiPlus = 0, PhiMinus, PsiPlus, PsiMinus };

struct BSAClickResult {
  bool success;
  PauliOperator correction_operation;
};
}  // namespace quisp::physical::types
