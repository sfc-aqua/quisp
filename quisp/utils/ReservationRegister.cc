/*
 * ReservationRegister.cc
 *
 *  Created on: Oct 14, 2024
 *      Author: paolo
 */

#include "ReservationRegister.h"

namespace quisp {
namespace utils {

void ReservationRegister::registerReservation(int qnic_addr, unsigned long ruleset_id) {
  if (auto target_entry = ruleset_id_to_qnic_addrs.find(ruleset_id); target_entry == ruleset_id_to_qnic_addrs.end()) {  // If entry already present, use that
    ruleset_id_to_qnic_addrs[ruleset_id] = std::set<int>();
  }

  auto& target_qnic_set = ruleset_id_to_qnic_addrs[ruleset_id];

  if (target_qnic_set.find(qnic_addr) != target_qnic_set.end()) {  // If qnic already in this entry, complain
    throw cRuntimeError("Error when registering QNIC reservation by ruleset id: QNIC Reservation already registered.");
  }

  target_qnic_set.insert(qnic_addr);

  if (auto search = qnic_addr_to_ruleset_id.find(qnic_addr); search != qnic_addr_to_ruleset_id.end()) {
    throw cRuntimeError("Error when registering QNIC reservation by qnic id: QNIC already reserved.");
  }
  qnic_addr_to_ruleset_id[qnic_addr] = ruleset_id;
}  // register a reservation with the provisional connection ID

void ReservationRegister::deleteReservationByQnicAddr(int qnic_addr) {
  auto target_reservation = qnic_addr_to_ruleset_id.find(qnic_addr);
  if (target_reservation == qnic_addr_to_ruleset_id.end()) throw cRuntimeError("Error when deleting QNIC reservation by QNIC address: qnic not reserved.");

  // fetching the relevant reservation in the RuleSet to Qnic addr register
  auto& target_qnic_set = ruleset_id_to_qnic_addrs[target_reservation->second];
  target_qnic_set.erase(qnic_addr);
  if (target_qnic_set.size() == 0) ruleset_id_to_qnic_addrs.erase(target_reservation->second);  // if this was the last qnic, delete the entry from the Ruleset to Qnic register

  qnic_addr_to_ruleset_id.erase(qnic_addr);  // Finally, delete the reservation from the Qnic to Ruleset ID register.
}

void ReservationRegister::deleteReservationByRulesetId(unsigned long ruleset_id) {
  auto target_reservation = ruleset_id_to_qnic_addrs.find(ruleset_id);
  if (target_reservation == ruleset_id_to_qnic_addrs.end()) throw cRuntimeError("Error when deleting QNIC reservation by ruleset id: QNIC not reserved.");

  for (int qnic_addr : target_reservation->second) {
    qnic_addr_to_ruleset_id.erase(qnic_addr);
  }
  ruleset_id_to_qnic_addrs.erase(ruleset_id);
}

void ReservationRegister::updateReservationId(unsigned long old_ruleset_id, unsigned long new_ruleset_id)  // update a reservation with the correct ruleset ID (once defined)
{
  auto reservation_to_update = ruleset_id_to_qnic_addrs.find(old_ruleset_id);
  if (reservation_to_update == ruleset_id_to_qnic_addrs.end()) throw cRuntimeError("Error when updating QNIC reservation ID: no such reservation");
  std::set<int> qnic_set = reservation_to_update->second;
  for (int qnic_addr : qnic_set) {
    deleteReservationByQnicAddr(qnic_addr);
    registerReservation(qnic_addr, new_ruleset_id);
  }
}

bool ReservationRegister::isQnicBusy(int qnic_addr) {
  auto it = qnic_addr_to_ruleset_id.find(qnic_addr);
  if (it == qnic_addr_to_ruleset_id.end()) {
    return false;
  }
  return true;
}

const std::set<int> ReservationRegister::getReservedQnics(unsigned long ruleset_id) const {
  auto search = ruleset_id_to_qnic_addrs.find(ruleset_id);
  if (search == ruleset_id_to_qnic_addrs.end()) {
    throw cRuntimeError("No qnics associated to this ruleset id!");
  } else
    return search->second;
}

const int ReservationRegister::getRsidToQnicAddrMapSize() const { return ruleset_id_to_qnic_addrs.size(); };
const int ReservationRegister::getQnicAddrToRsidMapSize() const { return qnic_addr_to_ruleset_id.size(); };
const std::map<unsigned long, std::set<int>>& ReservationRegister::getRsidToQnicAddrMap() const { return ruleset_id_to_qnic_addrs; };
const std::map<int, unsigned long>& ReservationRegister::getQnicAddrToRsidMap() const { return qnic_addr_to_ruleset_id; };

} /* namespace utils */
} /* namespace quisp */
