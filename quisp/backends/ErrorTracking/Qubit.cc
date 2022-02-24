#include "Qubit.h"

namespace quisp::backends::error_tracking {
   ErrorTrackingQubit::ErrorTrackingQubit(const QubitId id)
   : id(id) {};
   ErrorTrackingQubit::~ErrorTrackingQubit(){};
}
