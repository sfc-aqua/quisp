/*
 * ReservationRegistry.h
 *
 *  Created on: Oct 14, 2024
 *      Author: paolo
 */

#pragma once

#include <omnetpp.h>
#include <set>

using omnetpp::cRuntimeError;

namespace quisp {
namespace utils {

class ReservationRegistry {
 public:
  void registerReservation(unsigned long ruleset_id, int qnic_addr);
  void deleteReservationByQnicAddr(int qnic_addr);
  void deleteReservationByRulesetId(unsigned long ruleset_id);
  void updateReservationId(unsigned long new_ruleset_id, unsigned long old_ruleset_id);

 private:
  std::map<unsigned long, std::set<int>> ruleset_id_to_qnic_addrs;
  std::map<int, unsigned long> qnic_addr_to_ruleset_id;
};

} /* namespace utils */
} /* namespace quisp */
