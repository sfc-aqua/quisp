/** \file QUBIT.h
 *  \authors cldurand
 *  \date 2018/07/17
 *
 *  \brief QUBIT
 */
#ifndef QUISP_MODULES_QUBIT_H_
#define QUISP_MODULES_QUBIT_H_

#include <omnetpp.h>

#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
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

}  // namespace modules
}  // namespace quisp

#endif  // QUISP_MODULES_QUBIT_H_
