#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

namespace quisp::types {
struct QNodeAddr {
  QNodeAddr();
  explicit QNodeAddr(int host_addr);
  QNodeAddr(int network_addr, int host_addr);
  QNodeAddr(char* addr_str);
  QNodeAddr(const char* addr_str);
  int network_addr = 0;
  int host_addr = -1;

  bool operator==(const QNodeAddr& addr) const { return network_addr == addr.network_addr && host_addr == addr.host_addr; }
  bool operator==(QNodeAddr& addr) const { return network_addr == addr.network_addr && host_addr == addr.host_addr; }
  bool operator!=(const QNodeAddr& addr) const { return !(*this == addr); }
  bool operator!=(QNodeAddr& addr) const { return !(*this == addr); }
  bool operator<(const QNodeAddr& addr) const {
    if (network_addr < addr.network_addr) return true;
    if (network_addr > addr.network_addr) return false;
    if (host_addr < addr.host_addr) return true;
    return false;
  };
  bool operator>(const QNodeAddr& addr) const {
    if (*this < addr || *this == addr) return false;
    return true;
  };

  int toInt();
  static QNodeAddr fromInt(int);
};

std::ostream& operator<<(std::ostream& stream, const quisp::types::QNodeAddr& addr);

void to_json(nlohmann::json& j, const QNodeAddr& addr);
void from_json(const nlohmann::json& j, QNodeAddr& addr);
}  // namespace quisp::types

namespace std {
template <>
struct ::std::hash<quisp::types::QNodeAddr> {
 public:
  size_t operator()(const quisp::types::QNodeAddr& addr) const {
    auto seed = std::hash<int>()(addr.network_addr);
    // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
    seed ^= std::hash<int>()(addr.host_addr) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

std::string to_string(const quisp::types::QNodeAddr& addr);
}  // namespace std
