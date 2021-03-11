#include <tuple>
#include <iostream>
#include "bits/stdc++.h" 
using namespace std; 
#include <vector>
using std::begin;
using std::end;

vector<int> slicing(vector<int>& arr, int X, int Y) 
{ 
  
    // Starting and Ending iterators 
    auto start = arr.begin() + X; 
    auto end = arr.begin() + Y + 1; 
  
    // To store the sliced vector 
    vector<int> result(Y - X + 1); 
  
    // Copy vector using copy function() 
    copy(start, end, result.begin()); 
  
    // Return the final sliced vector 
    return result; 
} 


//Action 2A for the basis
int Action::initializeBasisAction() {
  int basis = 3; //bell
  return basis;
}

//Action 2B for the bell
bool Action::initializeBellAction() {
  bool successBell  = false;
  return successBell;
}

//Action 2C for the encodes
//std::outcomeList<int*, std::successBell<bool
//encode is like m?
std::map<int, vector<int>> Action::initializeEncode(std::encode<int,std:bv<int*){
  //case encodex
  //int arr[] = { 2,3,2 }; 
  //int encode = 1;
  int e[2];
  if(encode == 1){
     e[0] = 1;
     e[1] = 2;
  }
  else{
      e[0] = 2;
      e[1] = 1;
  }
  std::vector < int > vecOfint(bv, bv + sizeof(bv) / sizeof(int));
    //for (int str: vecOfStr){
    //  std::cout << str << std::endl;}
  std::map<int, vector<int>> encodedTree;
  std::vector<int> vec(0);
  for (int i=0; i<vecOfint.size(); i++){
    if (i == 0){
      int s = vecOfint[0];
      std::cout << e[0];
//      std::vector<int> vec(s, e[0]);
      vec.resize(s, e[0]);
    }

    else if (i%2 == 0){
      std::vector<int> temp = slicing(vecOfint, 0, i+1);
      auto multi = std::accumulate(begin(temp), end(temp), 1, std::multiplies<int>());
      //std::vector<int> vec(multi, e[0]);
      vec.resize(multi, e[0]);
    }

    else{
      std::vector<int> temp = slicing(vecOfint, 0, i+1);
      auto multi = std::accumulate(begin(temp), end(temp), 1, std::multiplies<int>());
      //std:vector<int> vec(multi, e[1]);
      vec.resize(multi, e[1]);
    }

    encodedTree.insert(std::make_pair(i+1, vec));
  }
  return encodedTree;
}

//Action 2D for thr msg
bool Action::initializeMsgAction(){
  bool msgSent = false;
  return msgSent;
}


//Action 5
std::map<int, tuple<int, bool, bool>> Action::measureAction(std::basis<int*){
  StationaryQubit *left_qubit = nullptr;
  StationaryQubit *right_qubit = nullptr;
  //the key is the name of qubit while the values are the basis and outcomes
  std::map<int, tuple<int, bool, bool>> outcomeList;
  for(int i=0; i<sizeof(basis);i++){
    left_qubit = getResource_fromTop_with_partner(left_resource, left_partner);
    right_qubit = getResource_fromTop_with_partner(right_resource, right_partner);
    if (basis[i] == 1){
      bool outcome_right = right_qubit -> measure_X();
      bool outcome_left = left_qubit -> measure_X(); 
    } else if (basis[i] == 2){
      bool outcome_right = right_qubit -> measure_Z();
      bool outcome_left = left_qubit -> measure_Z(); 
    } else if (basis[i] == 3){
      bool outcome_right = left_qubit->Hadamard_gate();
      bool outcome_left = right_qubit->CNOT_gate(left_qubit);
    }
    tuple<int,bool,bool> item(basis,outcome_right, outcome_left);
    outcomeList.insert(std::make_pair(i, item));
  }
  return outcomeList;
}

//Action 7
int* Action::finalizeAction(std::map<int, tuple<int, bool, bool>> *outcomeList){
  //int absaAdd = left_partner_qubit->stationaryQubit_address;
  //int endnodeAdd = right_partner_qubit->stationaryQubit_address;
  int* msg[outcomeList.size()]; //snce we only need a list of basis used
  std::map<int, tuple<int, bool, bool>::iterator it = outcomeList.begin();
  int i = 0;
  while(it !=outcomeList.end()){
    tuple <int, int, int> val = it->second;
    msg[i] = std::get<0>(val);
    i++;
  }
  bool msgSent = true;
  return msg;
}


//Action 9
int* Action::qkdInitializeAction(std::m<int){
  int* basisList = []; 
  bool msgNeeded = true;
  for(int i=0; i<m, i++){ 
    int randBasis = rand()%3+1; //if 1 >X, 2>Z, 3 > bell
    basisList[i] = randBasis;
    }
  return basisList;
}


//Action 11
std::map<int, tuple<int, bool, bool> Action::qkdMeasureAction(std::basis<int*, std::map<int, tuple<int, bool, bool>> *outcomeList){
  StationaryQubit *incomeQubit = nullptr;
  int outcome = meausre(incomeQubit,basis);
  for(int i=0; i<sizeof(basis);i++){
    left_qubit = getResource_fromTop_with_partner(incomeQubit, left_partner);
    right_qubit = getResource_fromTop_with_partner(incomeQubit, right_partner);
    if (basis[i] == 1){
      bool outcome_right = right_qubit -> measure_X();
      bool outcome_left = left_qubit -> measure_X(); 
    } else if (basis[i] == 2){
      bool outcome_right = right_qubit -> measure_Z();
      bool outcome_left = left_qubit -> measure_Z(); 
    } else if (basis[i] == 3){
      bool outcome_right = left_qubit->Hadamard_gate();
      bool outcome_left = right_qubit->CNOT_gate(left_qubit);
    }
    tuple<int,bool,booloutcome> item(basis,outcome_right, outcome_left);
    outcomeList.insert(std::make_pair(i, item));
  return outcomeList;
}

//Action 13
int* Action::qkdFinalizeAction(std::basis<int*){
  //int absaAdd = left_partner_qubit->stationaryQubit_address;
  //int endnodeAdd = right_partner_qubit->stationaryQubit_address;
  int* msg = *basisList; //this syntax is invalid
  bool msgNeeded = false;
  return msg;
}