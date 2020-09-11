/** \file QUBIT.h
 *  \authors cldurand
 *  \date 2018/07/17
 *
 *  \brief QUBIT
 */
#ifndef QUISP_MODULES_QUBIT_H_
#define QUISP_MODULES_QUBIT_H_

#include <modules/stationaryQubit.h>
#include <omnetpp.h>
using namespace omnetpp;

namespace quisp {
namespace modules {

struct QubitAddr_cons {
  QubitAddr_cons(const int node, const int qnic, const int qubit) : node_address(node), qnic_index(qnic), qubit_index(qubit) {}

  // QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
  int node_address;
  int qnic_index;
  int qubit_index;
};

struct QubitAddr {
  // QubitAddr(int node_addr, int qnic_index, int qubit_index):node_address(node_addr),qnic_index(qnic_index),qubit_index(qubit_index){}
  int node_address;
  int qnic_index;
  int qubit_index;
};

struct QubitState {
  // QubitState(int qubit_address, int qubit_index, int qnic_index, int node_address, bool busy, simtime_t time):addr(node_address,qnic_index, qubit_index),
  // entangled_addr(node_address,qnic_index, qubit_index), isBusy(busy), timestamp(time){}
  QubitAddr thisQubit_addr;
  // QubitAddr entangled_addr;//The entangled partner recognized. This could be wrong due to an error.
  // QubitAddr entangled_addr_actual;//The actual entangled partner
  // If entangled_addr != entangled_addr_actual, then operations do not do anything intended.
  bool isBusy;
  simtime_t timestamp;  // When the qubit became busy (emitted photon).
};

/*For resource management*/
// typedef std::multimap<int, QubitAddr> EntangledPairs;//entangled Node address -> list of qubits from new to old
typedef std::multimap<int, StationaryQubit*> EntangledPairs;  // entangled Node address -> pointer to that local qubit
typedef EntangledPairs* qnicResources;  // For each qnic. If the number of "qnic" is 3, then the size is 3.
/*For resource management over.*/

}  // namespace modules
}  // namespace quisp

#endif  // QUISP_MODULES_QUBIT_H_
