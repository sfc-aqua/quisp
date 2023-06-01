#pragma once

#include <gmock/gmock.h>
#include <modules/common_types.h>
#include <test_utils/ModuleType.h>
#include <test_utils/TestUtilFunctions.h>
#include "backends/interfaces/IQubit.h"
#include "gmock/gmock-function-mocker.h"
namespace quisp_test::mock_backends {
class MockBackendQubit : public quisp::backends::abstract::IQubit {
 public:
  MOCK_METHOD(void, setFree, (), (override));
};
}  // namespace quisp_test::mock_backends
