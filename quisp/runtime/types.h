/**
 * @file types.h
 * @brief this file contains the definitions of all the user-defined types
 * widely used alongside the runtime::RuleSet.
 */

#pragma once

#include <omnetpp/simtime.h>
#include <cstddef>
#include <string>

#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <modules/QRSA/QRSA.h>

namespace quisp::runtime {

using RuleId = int;

// these types are mainly used for describing type name in def_instruction.h
using String = std::string;

using IQubitRecord = quisp::modules::qrsa::IQubitRecord;

/// @brief measurement outcome for Instructions.
using MeasurementOutcome = quisp::backends::MeasurementOutcome;

/// @brief alias for omnetpp's simulation time.
using Time = omnetpp::SimTime;
/// @brief purification type for Instructions. see @ref rules::PurType enum.
using PurType = int;

/// @brief internal register id representation for Instructions.
enum class RegId : int { REG0, REG1, REG2, REG3, REG4 };
std::ostream& operator<<(std::ostream& stream, const RegId& value);

/**
 * @brief Program specify a ReturnCode during the execution. Then, the Runtime
 * determines to perform the action, execute the next Rule, or stop the RuleSet.
 */
enum class ReturnCode : int {
  /// @brief do nothing.
  NONE,
  /// @brief condition failed. stop the rule execution.
  COND_FAILED,
  /// @brief condition passed. will perform the action.
  COND_PASSED,
  /// @brief RuleSet terminated. will delete the RuleSet and the Runtime.
  RS_TERMINATED,
  /// @brief unrecorverable error raised. stop the simulation.
  ERROR,
};
std::ostream& operator<<(std::ostream& stream, const ReturnCode& value);

/// @brief internal class to describe QNode's address.
struct QNodeAddr {
  QNodeAddr(int val);
  int val;
};
std::ostream& operator<<(std::ostream& stream, const QNodeAddr& value);
bool operator<(const QNodeAddr& a, const QNodeAddr& b);
bool operator==(const QNodeAddr& a, const QNodeAddr& b);

/**
 * @brief describes Qubit id in a Program. This is like a local variable name
 * in a runtime::Program. Be careful, this is not used for RuleEngine or QNIC.
 */
struct QubitId {
  QubitId(int val);
  /// @brief hash function for unordered map
  size_t operator()(const QubitId&) const;
  int val;
};
std::ostream& operator<<(std::ostream& stream, const QubitId& value);
bool operator<(const QubitId& a, const QubitId& b);
bool operator==(const QubitId& a, const QubitId& b);

/// @brief label to annotate the instruction index in a Program.
struct Label {
  Label(std::string val);
  std::string val;
};
std::ostream& operator<<(std::ostream& stream, const Label& value);
bool operator==(const Label& a, const Label& b);

/// @brief a key of memory key-value store in a RuleSet
struct MemoryKey {
  MemoryKey(std::string key);
  std::string val;
};
std::ostream& operator<<(std::ostream& stream, const MemoryKey& key);
bool operator==(const MemoryKey& a, const MemoryKey& b);

using None = std::nullptr_t;

/// @brief utility type for storing a label and corresponding instruction index.
using LabelMap = std::unordered_map<Label, int>;

/// @brief basis for measurement instruction in a Program.
enum class Basis : int { Z, X, RANDOM };
std::ostream& operator<<(std::ostream& stream, const Basis& value);

}  // namespace quisp::runtime

namespace std {
// hash functions
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
