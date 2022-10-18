#pragma once

#include <cstddef>
#include <string>

#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <modules/QRSA/QRSA.h>

namespace quisp::runtime {

using RuleId = int;
using String = std::string;

using IQubitRecord = quisp::modules::qrsa::IQubitRecord;
using MeasurementOutcome = quisp::modules::measurement_outcome;

// these types are mainly used for describing type name in def_instruction.h
enum class RegId : int { REG0, REG1, REG2, REG3 };
std::ostream& operator<<(std::ostream& stream, const RegId& value);

enum class ReturnCode : int { NONE, COND_FAILED, COND_PASSED };
std::ostream& operator<<(std::ostream& stream, const ReturnCode& value);

struct QNodeAddr {
  QNodeAddr(int val);
  int val;
};
std::ostream& operator<<(std::ostream& stream, const QNodeAddr& value);
bool operator<(const QNodeAddr& a, const QNodeAddr& b);
bool operator==(const QNodeAddr& a, const QNodeAddr& b);

struct QubitId {
  QubitId(int val);
  size_t operator()(const QubitId&) const;
  int val;
};
std::ostream& operator<<(std::ostream& stream, const QubitId& value);
bool operator<(const QubitId& a, const QubitId& b);
bool operator==(const QubitId& a, const QubitId& b);

struct Label {
  Label(std::string val);
  std::string val;
};
std::ostream& operator<<(std::ostream& stream, const Label& value);
bool operator==(const Label& a, const Label& b);

struct MemoryKey {
  MemoryKey(std::string key);
  std::string val;
};
std::ostream& operator<<(std::ostream& stream, const MemoryKey& key);
bool operator==(const MemoryKey& a, const MemoryKey& b);

using None = std::nullptr_t;
enum class Basis : int { Z, X, RANDOM };
std::ostream& operator<<(std::ostream& stream, const Basis& value);

}  // namespace quisp::runtime

namespace std {
template <>
struct ::std::hash<quisp::runtime::QNodeAddr> {
 public:
  size_t operator()(const quisp::runtime::QNodeAddr& addr) const { return std::hash<int>()(addr.val); }
};

template <>
struct ::std::hash<quisp::runtime::QubitId> {
 public:
  size_t operator()(const quisp::runtime::QubitId& id) const { return std::hash<int>()(id.val); }
};

template <>
struct ::std::hash<quisp::runtime::MemoryKey> {
 public:
  size_t operator()(const quisp::runtime::MemoryKey& key) const { return std::hash<std::string>()(key.val); }
};

template <>
struct ::std::hash<quisp::runtime::Label> {
 public:
  size_t operator()(const quisp::runtime::Label& label) const { return std::hash<std::string>()(label.val); }
};

template <>
struct ::std::hash<std::pair<quisp::runtime::QNodeAddr, quisp::runtime::RuleId>> {
 public:
  size_t operator()(const std::pair<quisp::runtime::QNodeAddr, quisp::runtime::RuleId>& p) const {
    auto seed = std::hash<int>()(p.first.val);
    // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
    seed ^= std::hash<int>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

}  // namespace std
