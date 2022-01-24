#include "Condition.h"
#include <memory>
#include "Clause.h"
namespace quisp::rules {
void Condition::addClause(std::unique_ptr<BaseClause> clause) { clauses.push_back(*clause); }
}  // namespace quisp::rules
