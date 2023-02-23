#include "QNodeAddr.h"
#include <string.h>
#include "omnetpp/cexception.h"

namespace quisp::types {
QNodeAddr::QNodeAddr() {}
QNodeAddr::QNodeAddr(int host_addr) : network_addr(0), host_addr(host_addr) {}
QNodeAddr::QNodeAddr(int network_addr, int host_addr) : network_addr(network_addr), host_addr(host_addr) {}
QNodeAddr::QNodeAddr(char* addr_str) {
  const char* sep = ".";
  auto* p = strtok(addr_str, sep);
  if (p == nullptr) {
    return;
  }
  network_addr = atoi(p);
  p = strtok(nullptr, ".");
  host_addr = atoi(p);
}

QNodeAddr::QNodeAddr(const char* addr_str) {
  char* s = (char*)malloc(strlen(addr_str));
  strcpy(s, addr_str);
  auto* p = strtok(s, ".");
  if (p == nullptr) {
    return;
  }
  network_addr = atoi(p);
  p = strtok(nullptr, ".");
  host_addr = atoi(p);
}

std::ostream& operator<<(std::ostream& stream, const QNodeAddr& addr) {
  stream << std::to_string(addr.network_addr) << "." << std::to_string(addr.host_addr);
  return stream;
}

void to_json(nlohmann::json& j, const QNodeAddr& addr) {
  auto s = std::to_string(addr.network_addr) + "." + std::to_string(addr.host_addr);
  j = s;
}

void from_json(const nlohmann::json& j, QNodeAddr& addr) {
  if (!j.is_string()) {
    throw new omnetpp::cRuntimeError("failed to parse json: QNodeAddr should be a string");
  }
  auto s = std::string(j);
  char* addr_str = (char*)malloc(s.length() + 1);
  strcpy(addr_str, s.c_str());
  auto a = QNodeAddr{addr_str};
  addr.network_addr = a.network_addr;
  addr.host_addr = a.host_addr;
}

}  // namespace quisp::types

namespace std {
std::string to_string(const quisp::types::QNodeAddr& addr) {
  std::stringstream ss;
  ss << addr;
  return ss.str();
}
}  // namespace std
