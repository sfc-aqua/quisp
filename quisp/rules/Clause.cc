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

/*
bool FidelityClause::check(qnicResources* resources) const {
    stationaryQubit* qubit = NULL;
    checkQnic();//This is not doing anything...
    if(qubit = getQubit(resources, qnic_type, qnic_id, partner, resource)){
        return (qubit->getFidelity() >= threshold);
    }
    return false;
}*/

bool FidelityClause::check(std::multimap<int, StationaryQubit*> resource) const {
  StationaryQubit* qubit = nullptr;
  /*checkQnic();//This is not doing anything...
  if(qubit = getQubit(resources, qnic_type, qnic_id, partner, resource)){
      return (qubit->getFidelity() >= threshold);
  }
  return false;*/
}

bool EnoughResourceClause::check(std::multimap<int, StationaryQubit*> resource) const {
  // std::cout<<"!!In enough clause \n";
  bool enough = false;
  int num_free = 0;

  for (std::multimap<int, StationaryQubit*>::iterator it = resource.begin(); it != resource.end(); ++it) {
    if (it->first == partner) {
      if (!it->second->isLocked()) {  // here must have loop
        num_free++;
      }
      if (num_free >= num_resource_required) {
        enough = true;
      }
    }
  }
  // std::cout<<"Enough = "<<enough<<"\n";
  return enough;
}

bool EnoughResourceClauseLeft::check(std::multimap<int, StationaryQubit*> resource) const {
  // std::cout<<"!!In enough clause \n";
  bool enough = false;
  int num_free = 0;

  for (std::multimap<int, StationaryQubit*>::iterator it = resource.begin(); it != resource.end(); ++it) {
    if (it->first == partner_left) {
      if (!it->second->isLocked()) {  // here must have loop
        num_free++;
      }
      if (num_free >= num_resource_required_left) {
        enough = true;
      }
    }
  }
  if (enough) {
    EV << "You have enough resource between " << partner_left << "\n";
  } else {
    EV << "You don't have enough resource between " << partner_left << "\n";
  }
  // std::cout<<"Enough = "<<enough<<"\n";
  return enough;
}

bool EnoughResourceClauseRight::check(std::multimap<int, StationaryQubit*> resource) const {
  // std::cout<<"!!In enough clause \n";
  bool enough = false;
  int num_free = 0;

  for (std::multimap<int, StationaryQubit*>::iterator it = resource.begin(); it != resource.end(); ++it) {
    if (it->first == partner_right) {
      if (!it->second->isLocked()) {  // here must have loop
        num_free++;
      }
      if (num_free >= num_resource_required_right) {
        enough = true;
      }
    }
  }
  if (enough) {
    EV << "You have enough resource between " << partner_right << "\n";
  } else {
    EV << "You don't have enough resource between " << partner_right << "\n";
  }
  // std::cout<<"Enough = "<<enough<<"\n";
  return enough;
}

/*
bool MeasureCountClause::check(qnicResources* resources) const {
    //EV<<"MeasureCountClause invoked!!!! \n";
    if(current_count<max_count){
        current_count++;//Increment measured counter.
        EV<<"Measurement count is now "<<current_count<<" < "<<max_count<<"\n";
        return true;
    }
    else{
        EV<<"Count is enough";
        return false;
    }
}*/

bool MeasureCountClause::check(std::multimap<int, StationaryQubit*> resources) const {
  // std::cout<<"MeasureCountClause invoked!!!! \n";
  if (current_count < max_count) {
    current_count++;  // Increment measured counter.
    // std::cout<<"Measurement count is now "<<current_count<<" < "<<max_count<<"\n";
    return true;
  } else {
    // std::cout<<"Count is enough\n";
    return false;
  }
}

bool MeasureCountClause::checkTerminate(std::multimap<int, StationaryQubit*> resources) const {
  EV << "Tomography termination clause invoked.\n";
  bool done = false;
  if (current_count >= max_count) {
    // EV<<"TRUE: Current count = "<<current_count<<" >=  "<<max_count<<"(max)\n";
    done = true;
  }
  return done;
}

/*
bool MeasureCountClause::checkTerminate(qnicResources* resources) const {
    EV<<"Tomography termination clause invoked.\n";
    bool done = false;
    if(current_count >=max_count){
        EV<<"TRUE: Current count = "<<current_count<<" >=  "<<max_count<<"(max)\n";
        done = true;
    }
    return done;
}*/

/*
bool PurificationCountClause::check(qnicResources* resources) const {
    stationaryQubit* qubit = NULL;
    //checkQnic();//This is not doing anything...

    qubit = getQubitPurified(resources, qnic_type, qnic_id, partner, num_purify_must);
    if(qubit != nullptr){
        return true;//There is a qubit that has been purified "num_purify_must" times.
    }else{
        return false;
    }
}*/

bool PurificationCountClause::check(std::multimap<int, StationaryQubit*> resource) const {
  StationaryQubit* qubit = nullptr;
  // checkQnic();//This is not doing anything...

  /*
  qubit = getQubitPurified(resources, qnic_type, qnic_id, partner, num_purify_must);
  if(qubit != nullptr){
      return true;//There is a qubit that has been purified "num_purify_must" times.
  }else{
      return false;
  }*/
}

/*
bool PurificationCountClause::checkTerminate(qnicResources* resources) const {
        return false;
}*/

// Clause *EXAMPLE_CLAUSE = new FidelityClause(0,0,.6);

}  // namespace rules
}  // namespace quisp
