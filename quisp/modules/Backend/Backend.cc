#include "Backend.h"

namespace quisp::modules::backend {

BackendContainer::BackendContainer()
#ifdef ENABLE_PYTHON
    : interpreter(pybind11::scoped_interpreter{})
#endif
{
}

BackendContainer::~BackendContainer() {}

}  // namespace quisp::modules::backend
