#include <gmock/gmock.h>

#include "utils/UtilFunctions.h"

namespace {
using quisp::utilFunctions::mapToLabel;

TEST(UtilFunctionsTest, mapToLabelTest1) {
  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<double, ErrorLabel> weights = {{0.2, ErrorLabel::NO_ERR}, {0.5, ErrorLabel::X}, {0.7, ErrorLabel::Z}, {1.0, ErrorLabel::Y}};

  double rand = 0.2;
  ErrorLabel r = mapToLabel(weights, rand);

  EXPECT_EQ(r, ErrorLabel::NO_ERR);
}

TEST(UtilFunctionsTest, mapToLabelTest2) {
  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<double, ErrorLabel> weights = {{0.2, ErrorLabel::NO_ERR}, {0.5, ErrorLabel::X}, {0.7, ErrorLabel::Z}, {1.0, ErrorLabel::Y}};

  double rand = 0.5;
  ErrorLabel r = mapToLabel(weights, rand);

  EXPECT_EQ(r, ErrorLabel::X);
}

TEST(UtilFunctionsTest, mapToLabelTest3) {
  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<double, ErrorLabel> weights = {{0.2, ErrorLabel::NO_ERR}, {0.5, ErrorLabel::X}, {0.7, ErrorLabel::Z}, {1.0, ErrorLabel::Y}};

  double rand = 0.7;
  ErrorLabel r = mapToLabel(weights, rand);

  EXPECT_EQ(r, ErrorLabel::Z);
}

TEST(UtilFunctionsTest, mapToLabelTest4) {
  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<double, ErrorLabel> weights = {{0.2, ErrorLabel::NO_ERR}, {0.5, ErrorLabel::X}, {0.7, ErrorLabel::Z}, {1.0, ErrorLabel::Y}};

  double rand = 1.0;
  ErrorLabel r = mapToLabel(weights, rand);

  EXPECT_EQ(r, ErrorLabel::Y);
}
}  // namespace