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
  // EV<<"EnoughResourceClauseLeft\n";
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
  // if (enough) {
  //   EV << "You have enough resource between " << partner_left << "\n";
  // } else {
  //   EV << "You don't have enough resource between " << partner_left << "\n";
  // }
  // std::cout<<"Enough = "<<enough<<"\n";
  return enough;
}

bool EnoughResourceClauseRight::check(std::multimap<int, StationaryQubit*> resource) const {
  // EV<<"EnoughResourceClauseRight\n";
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
  // if (enough) {
  //   EV << "You have enough resource between " << partner_right << "\n";
  // } else {
  //   EV << "You don't have enough resource between " << partner_right << "\n";
  // }
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
}


// //ABSA clauses start here
// //Algorithm 1 Clause
// bool initConditionalClause::check(std::arrivalTimeList<int*){
//   bool initTime = false;
//   //get current time
//   int currentTime = simTime();
//   if (currentTime < arrivalTimeList[0]){
//     initTime = true;
//   }
//   return initTime;
// }
  
// //Algorithm 3 Clause
// bool MeasureConditionalClause::check(std::arrivalTimeList<int*){
//   int currentTime = simTime();
//   bool measurementNeeded = false;
//   if (arrivalTimeList[0] <= currentTime && currentTime <= arrivalTimeList[-1]){
//     measurementNeeded = true;
//   }
//   return measurementNeeded;
// }
  
// //Algorithm 4 Clause
// int postBellConditionalClause::check(std::map<int, tuple<int, int, int>> *outcomeList, std::successBell<bool){
//   int basis; //x
//   std::map<int, tuple<int, int, int>::iterator itr;
//   itr = outcomeList.end();
//   --itr;
//   //itr-> first == is the key
//   //itr->second == is the value
//   //need to checck if the measurement is successful or not
//  // if (successBell == true or itr->second.successful() == false){
//   if (successBell == true){
//     basis = 2; //z
//   }
//   else{
//     basis = 1;
//   }
//   return basis;
// }
  
  
//  //Algorithm 6 Clause
// bool finalConditionalClause::check(std::arrivalTimeList<int*, std::msgSent<bool){
//   //get current time
//   int currentTime = simTime();
//   bool msgNeeded = false;
//   if (currentTime > arrivalTimeList[-1] && msgSent == false){
//     msgNeeded = true;
//   }
//   return msgNeeded;
// }
  
 
// //Algorithm 8 Clause
// bool qkdInitConditionalClause(std::arrivalTimeList<int*){
//   bool initNeeded = false;
//   int currentTime = simTime();
//   if (currentTime < arrivalTimeList[0]){
//     initNeeded = true;
//   }
//   return initNeeded;
// }
  
  

// //Algorithm 10A Clause
// //needs to be divided into two clause >> multiple returns
// bool qkdMeasureConditionClause(std::arrivalTimeList<int*, std::basisList<int*){
//   bool measurementNeeded = false;
//   int currentTime = simTime();
//   if (arrivalTimeList[0] <= currentTime and currentTime <= arrivalTimeList[-1]){
//     measurementNeeded = true;
//   }
//   return measurementNeeded;
// }

// //Algorithm 10B Clause
// int qkdBasisConditionClause(std::arrivalTimeList<int*, std::basisList<int*){
//   int currentTime = simTime();
//   int basis;
//   int index = get_index(currentTime, int *arrivalTimeList);
//   if (arrivalTimeList[0] <= currentTime and currentTime <= arrivalTimeList[-1]){
//     basis = basisList[index];
//   }
//   return basis;
// }
  
// //Algorithm 12 Clause
// bool qkdFinalConditionClause(std::arrivalTimeList<int*){
//   int currentTime = simTime();
//   bool finalNeeded = false;
//   if(currentTime > arrivalTimeList[-1]){
//     finalNeeded = true;
//   }
//   return finalNeeded;
// }


}  // namespace rules
}  // namespace quisp
