/** \file Clause.cc
 *
 *  \authors cldurand,,takaakimatsuo
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#include "Clause.h"
#include "tools.h"

namespace quisp {
namespace rules {

bool FidelityClause::check(qnicResources* resources) const {
    stationaryQubit* qubit = NULL;
    checkQnic();//This is not doing anything...
    if(qubit = getQubit(resources, qnic_type, qnic_id, partner, resource)){
        return (qubit->getFidelity() >= threshold);
    }
    return false;
}

bool MeasureCountClause::check(qnicResources* resources) const {
    EV<<"MeasureCountClause invoked!!!! \n";
    if(current_count<max_count){
        current_count++;//Increment measured counter.
        EV<<"Measurement count is now "<<current_count<<" < "<<max_count<<"\n";
        return true;
    }
    else{
        EV<<"Count is enough";
        return false;
    }
}



bool MeasureCountClause::checkTerminate(qnicResources* resources) const {
    EV<<"Tomography termination clause invoked.\n";
    bool done = false;
    if(current_count >=max_count){
        EV<<"TRUE: Current count = "<<current_count<<" >=  "<<max_count<<"(max)\n";
        done = true;
    }
    return done;
}


bool PurificationCountClause::check(qnicResources* resources) const {
    stationaryQubit* qubit = NULL;
    //checkQnic();//This is not doing anything...

    qubit = getQubitPurified(resources, qnic_type, qnic_id, partner, num_purify_must);
    if(qubit != nullptr){
        return true;//There is a qubit that has been purified "num_purify_must" times.
    }else{
        return false;
    }
}

bool PurificationCountClause::checkTerminate(qnicResources* resources) const {
        return false;
}




Clause *EXAMPLE_CLAUSE = new FidelityClause(0,0,.6);

} // namespace rules
} // namespace quisp
