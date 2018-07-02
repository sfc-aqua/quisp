/** \file QNIC.h
 *  \authors cldurand
 *  \date 2018/06/29
 *
 *  \brief QNIC
 */
#ifndef QUISP_MODULES_QNIC_H_
#define QUISP_MODULES_QNIC_H_

#include <omnetpp.h>
using namespace omnetpp;

namespace quisp {
namespace modules {

typedef enum _QNIC_type:int {
    QNIC_E,  /**< Emitter QNIC          */
    QNIC_R,  /**< Receiver QNIC         */
    QNIC_RP, /**< Passive Receiver QNIC */
    QNIC_N, /** Just to make the size of the array = the number of qnics*/
} QNIC_type;

static const char* QNIC_names[QNIC_N] = {
    [QNIC_E]="qnic",
    [QNIC_R]="qnic_r",
    [QNIC_RP]="qnic_rp",
};

typedef struct _QNIC_id {
    QNIC_type type;
    int index;
    int address;
} QNIC_id;

typedef struct _QNIC : _QNIC_id {
    cModule *pointer;
} QNIC;

} // namespace modules
} // namespace quisp

#endif//QUISP_MODULES_QNIC_H_
