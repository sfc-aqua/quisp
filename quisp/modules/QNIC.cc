/** \file QNIC.cc
 *  \authors NozomiTanetani
 *  \date 2020/3/15
 *
 *  \brief QNIC
 */
#include "QNIC.h"
#include <omnetpp.h>

namespace quisp{
namespace modules{

void QNIC::initialize(){
    is_allocated = false;
}

void QNIC::Allocate(){
    is_allocated = true;
}

void QNIC::Deallocate(){
    is_allocated = false;
}

bool QNIC::isAllocated(){
    return is_allocated;
}

}
}