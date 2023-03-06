#include "QNodeAddr.h"
#include <gtest/gtest.h>

using nlohmann::json;
using quisp::types::QNodeAddr;
namespace {

TEST(QNodeAddr, defaultCtor) {
  QNodeAddr addr;
  EXPECT_EQ(addr.network_addr, 0);
  EXPECT_EQ(addr.host_addr, -1);
}

TEST(QNodeAddr, addrPair) {
  auto addr = QNodeAddr{7, 8};
  EXPECT_EQ(addr.network_addr, 7);
  EXPECT_EQ(addr.host_addr, 8);
};

TEST(QNodeAddr, equality) {
  auto addr1 = QNodeAddr{7, 8};
  auto addr2 = QNodeAddr{7, 8};
  auto addr3 = QNodeAddr{7, 9};

  EXPECT_TRUE(addr1 == addr2);
  EXPECT_TRUE(addr1 != addr3);
  EXPECT_TRUE(addr2 != addr3);
}

TEST(QNodeAddr, toString) {
  std::stringstream ss;
  ss << QNodeAddr(1, 2);
  EXPECT_EQ(ss.str(), "1.2");
}

TEST(QNodeAddr, fromString) {
  char addr_str[] = "123.45";
  QNodeAddr addr{addr_str};
  EXPECT_EQ(addr.network_addr, 123);
  EXPECT_EQ(addr.host_addr, 45);
}

TEST(QNodeAddr, fromConstString) {
  const char addr_str[] = "123.45";
  QNodeAddr addr{addr_str};
  EXPECT_EQ(addr.network_addr, 123);
  EXPECT_EQ(addr.host_addr, 45);
}

TEST(QNodeAddr, toJson) {
  QNodeAddr addr{1, 4};
  json j;
  to_json(j, addr);
  EXPECT_STREQ(j.dump().c_str(), "\"1.4\"");
}

TEST(QNodeAddr, toInt) {
  QNodeAddr addr{12, 34};
  int val = addr.toInt();
  EXPECT_EQ(QNodeAddr::fromInt(val), addr);
}
}  // namespace
