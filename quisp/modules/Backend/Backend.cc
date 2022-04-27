#include "Backend.h"

namespace quisp::modules::backend {

BackendContainer::BackendContainer() : interpreter(pybind11::scoped_interpreter{}) {}

BackendContainer::~BackendContainer() {}

}  // namespace quisp::modules::backend
