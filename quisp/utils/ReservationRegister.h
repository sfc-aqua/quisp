/*
 * ReservationRegister.h
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

class ReservationRegister {
 public:
  void registerReservation(int qnic_addr, unsigned long ruleset_id);
  void deleteReservationByQnicAddr(int qnic_addr);
  void deleteReservationByRulesetId(unsigned long ruleset_id);
  void updateReservationId(unsigned long old_ruleset_id, unsigned long new_ruleset_id);
  bool isQnicBusy(int qnic_addr);

  const int getRsidToQnicAddrMapSize() const;
  const int getQnicAddrToRsidMapSize() const;
  const std::map<unsigned long, std::set<int>>& getRsidToQnicAddrMap() const;
  const std::map<int, unsigned long>& getQnicAddrToRsidMap() const;

 private:
  std::map<unsigned long, std::set<int>> ruleset_id_to_qnic_addrs;
  std::map<int, unsigned long> qnic_addr_to_ruleset_id;
};

} /* namespace utils */
} /* namespace quisp */
