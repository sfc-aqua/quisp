#include <gmock/gmock.h>

#include "utils/UtilFunctions.h"

namespace {
using quisp::util_functions::samplingWithWeights;

TEST(UtilFunctionsTest, samplingWithWeightsTest1) {
  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<ErrorLabel, double> weights = {{ErrorLabel::NO_ERR, 0.2}, {ErrorLabel::X, 0.3}, {ErrorLabel::Z, 0.3}, {ErrorLabel::Y, 0.2}};

  ErrorLabel r = samplingWithWeights(weights, 0.2);
  EXPECT_EQ(r, ErrorLabel::NO_ERR);

  r = samplingWithWeights(weights, 0.5);
  EXPECT_EQ(r, ErrorLabel::X);

  r = samplingWithWeights(weights, 0.8);
  EXPECT_EQ(r, ErrorLabel::Z);

  r = samplingWithWeights(weights, 1.0);
  EXPECT_EQ(r, ErrorLabel::Y);
}

TEST(UtilFunctionsTest, samplingWithWeightsTest2) {
  enum class ErrorLabel : int { NO_ERR, X, Z, Y };
  std::map<ErrorLabel, double> weights = {{ErrorLabel::NO_ERR, 2}, {ErrorLabel::X, 3}, {ErrorLabel::Z, 3}, {ErrorLabel::Y, 2}};

  ErrorLabel r = samplingWithWeights(weights, 0.2);
  EXPECT_EQ(r, ErrorLabel::NO_ERR);

  r = samplingWithWeights(weights, 0.5);
  EXPECT_EQ(r, ErrorLabel::X);

  r = samplingWithWeights(weights, 0.8);
  EXPECT_EQ(r, ErrorLabel::Z);

  r = samplingWithWeights(weights, 1.0);
  EXPECT_EQ(r, ErrorLabel::Y);
}
}  // namespace