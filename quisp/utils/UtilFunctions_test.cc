#include <gmock/gmock.h>

#include "utils/UtilFunctions.h"

namespace {
using quisp::utilFunctions::getLabel;

TEST(UtilFunctionsTest, getLabelTest) {
  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<double, ErrorLabel> weights = {
      {0.2, ErrorLabel::NO_ERR}, {0.5, ErrorLabel::X}, {0.7, ErrorLabel::Z}, {1.0, ErrorLabel::Y}};

  double rand = 0.2;
  ErrorLabel r = getLabel(weights, rand);

  EXPECT_EQ(r, ErrorLabel::NO_ERR);
}
}