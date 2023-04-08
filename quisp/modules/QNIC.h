/** \file QNIC.h
 *  \authors cldurand
 *  \date 2018/06/29
 *
 *  \brief QNIC
 */

#pragma once

#include <omnetpp.h>
#include <nlohmann/json.hpp>

using namespace omnetpp;

namespace quisp::modules {

using json = nlohmann::json;
typedef enum : int {
  QNIC_E, /**< Emitter QNIC          */
  QNIC_R, /**< Receiver QNIC         */
  QNIC_RP, /**< Passive Receiver QNIC */
  QNIC_N, /** Just to make the size of the array = the number of qnics*/
} QNIC_type;

NLOHMANN_JSON_SERIALIZE_ENUM(QNIC_type, {
                                            {QNIC_E, "QNIC_E"},
                                            {QNIC_R, "QNIC_R"},
                                            {QNIC_RP, "QNIC_RP"},
                                        })

static const char* QNIC_names[QNIC_N] = {
    "qnic",
    "qnic_r",
    "qnic_rp",
};

struct QNIC {
  QNIC_type type;
  int index;
  // QNIC's self_qnic_address
  int address;
  // Pointer to that particular QNIC.
  cModule* pointer = nullptr;
};

using QNicPairInfo = std::pair<QNIC, QNIC>;
}  // namespace quisp::modules

namespace std {
template <>
class hash<pair<quisp::modules::QNIC_type, int>> {
 public:
  /**
   * @brief hash function for pair<QNIC_type, int> this only work assuming each node won't have more than 10,000 QNICs
   *
   * @return std::size_t the hash result
   */
  std::size_t operator()(pair<quisp::modules::QNIC_type, int> const& key) const noexcept { return std::hash<int>()((int)key.first * 10000 + key.second); }
};
}  // namespace std
