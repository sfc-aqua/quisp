#pragma once

#include <gmock/gmock.h>
#include <modules/common_types.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>
#include "backends/interfaces/IQubit.h"
#include "gmock/gmock-function-mocker.h"
namespace quisp_test::mock_backends {
class MockBackendQubit : public quisp::backends::abstract::IQubit {
 public:
  MOCK_METHOD(void, setFree, (), (override));
  MOCK_METHOD(void, setMaximallyEntangledWith, (IQubit * partner_qubit), (override));
};
}  // namespace quisp_test::mock_backends
