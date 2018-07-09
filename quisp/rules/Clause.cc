/** \file Clause.cc
 *
 *  \authors cldurand
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#include "Clause.h"

namespace quisp {
namespace rules {

int FidelityClause::check() const { return 0; }

Clause *EXAMPLE_CLAUSE = new FidelityClause(42);

} // namespace rules
} // namespace quisp
