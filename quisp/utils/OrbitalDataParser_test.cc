#include <gtest/gtest.h>

#include <test_utils/TestUtils.h>

#include <fstream>

#include "OrbitalDataParser.h"

#include <cstdio>

using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;

namespace {

class OrbitalDataParserTest : public ::testing::Test {
 protected:
  void SetUp() {
    csv_to_generate.open("channels/test_csv.csv");
    csv_to_generate << "200,100000\n";
    csv_to_generate << "300,300000\n";
    csv_to_generate << "400,200000\n";
    csv_to_generate.close();
    csv_parser = new OrbitalDataParser("channels/test_csv.csv");
  }
  void TearDown() { std::remove("channels/test_csv.csv"); }

  OrbitalDataParser* csv_parser;
  std::ofstream csv_to_generate;
};

TEST_F(OrbitalDataParserTest, lowerBound) {
  ASSERT_DOUBLE_EQ(csv_parser->getLowestDatapoint(), 200);
  ASSERT_DOUBLE_EQ(csv_parser->getLowestDatavalue(), 100000);
}

TEST_F(OrbitalDataParserTest, upperBound) {
  ASSERT_DOUBLE_EQ(csv_parser->getHighestDatapoint(), 400);
  ASSERT_DOUBLE_EQ(csv_parser->getHighestDatavalue(), 200000);
}

TEST_F(OrbitalDataParserTest, lowerThanLB) { ASSERT_DOUBLE_EQ(csv_parser->getPropertyAtTime(100), 100000); }

TEST_F(OrbitalDataParserTest, higherThanUB) { ASSERT_DOUBLE_EQ(csv_parser->getPropertyAtTime(500), 200000); }

TEST_F(OrbitalDataParserTest, normalOperation) {
  ASSERT_DOUBLE_EQ(csv_parser->getPropertyAtTime(250), 200000);
  ASSERT_DOUBLE_EQ(csv_parser->getPropertyAtTime(300), 300000);
  ASSERT_DOUBLE_EQ(csv_parser->getPropertyAtTime(350), 250000);
  ASSERT_DOUBLE_EQ(csv_parser->getPropertyAtTime(234.5), 169000);
  ASSERT_DOUBLE_EQ(csv_parser->getPropertyAtTime(287.4), 274800);
}

}  // namespace
