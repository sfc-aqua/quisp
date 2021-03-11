#include "Clause.h"
#include "tools.h"

namespace quisp {
namespace rules {


//ABSA clauses start here
//Algorithm 1 Clause
bool initConditionalClause::check(std::arrivalTimeList<int*){
  bool initTime = false;
  //get current time
  int currentTime = simTime();
  if (currentTime < arrivalTimeList[0]){
    initTime = true;
  }
  return initTime;
}
  
//Algorithm 3 Clause
bool MeasureConditionalClause::check(std::arrivalTimeList<int*){
  int currentTime = simTime();
  bool measurementNeeded = false;
  if (arrivalTimeList[0] <= currentTime && currentTime <= arrivalTimeList[-1]){
    measurementNeeded = true;
  }
  return measurementNeeded;
}
  
//Algorithm 4 Clause
int postBellConditionalClause::check(std::map<int, tuple<int, int, int>> *outcomeList, std::successBell<bool){
  int basis; //x
  std::map<int, tuple<int, int, int>::iterator itr;
  itr = outcomeList.end();
  --itr;
  //itr-> first == is the key
  //itr->second == is the value
  //need to checck if the measurement is successful or not
 // if (successBell == true or itr->second.successful() == false){
  if (successBell == true){
    basis = 2; //z
  }
  else{
    basis = 1;
  }
  return basis;
}
  
  
 //Algorithm 6 Clause
bool finalConditionalClause::check(std::arrivalTimeList<int*, std::msgSent<bool){
  //get current time
  int currentTime = simTime();
  bool msgNeeded = false;
  if (currentTime > arrivalTimeList[-1] && msgSent == false){
    msgNeeded = true;
  }
  return msgNeeded;
}
  
 
//Algorithm 8 Clause
bool qkdInitConditionalClause(std::arrivalTimeList<int*){
  bool initNeeded = false;
  int currentTime = simTime();
  if (currentTime < arrivalTimeList[0]){
    initNeeded = true;
  }
  return initNeeded;
}
  
  

//Algorithm 10A Clause
//needs to be divided into two clause >> multiple returns
bool qkdMeasureConditionClause(std::arrivalTimeList<int*, std::basisList<int*){
  bool measurementNeeded = false;
  int currentTime = simTime();
  if (arrivalTimeList[0] <= currentTime and currentTime <= arrivalTimeList[-1]){
    measurementNeeded = true;
  }
  return measurementNeeded;
}
  
//Algorithm 10B Clause
int qkdBasisConditionClause(std::arrivalTimeList<int*, std::basisList<int*){
  int currentTime = simTime();
  int basis;
  int index = get_index(currentTime, int *arrivalTimeList);
  if (arrivalTimeList[0] <= currentTime and currentTime <= arrivalTimeList[-1]){
    basis = basisList[index];
  }
  return basis;
}
  
//Algorithm 12 Clause
bool qkdFinalConditionClause(std::arrivalTimeList<int*){
  int currentTime = simTime();
  bool finalNeeded = false;
  if(currentTime > arrivalTimeList[-1]){
    finalNeeded = true;
  }
  return finalNeeded;
}

}  // namespace rules
}  // namespace quisp