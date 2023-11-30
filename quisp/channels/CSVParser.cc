/*
 * CSVParser.cc
 *
 *  Created on: Nov 28, 2023
 *      Author: paolo
 */

#include "CSVParser.h"

CSVParser::CSVParser(const string filename) {
    file.open(filename);
    if (!file.is_open()) throw cRuntimeError("Couldn't find CSV file!");
    string line;
    int key = 0;
    double val = 0;
    char sep; //throwaway
    while (file >> line) {
        std::istringstream ss(line);
        ss >> key >> sep >> val;
        property.insert(std::pair<int,float>(key,val));
    }
    return;
}

double CSVParser::getPropertyAtTime(const double time) {
    if (property.find(time) == property.end()) {
      // not found
        float lowWeight = 0,highWeight = 0;
        int lowKey = 0, highKey = 0;
        lowKey = property.lower_bound(time)->first;
        highKey = property.upper_bound(time)->first;

        lowWeight = simTime().dbl() - lowKey;
        highWeight = highKey - simTime().dbl();

        return (lowWeight*property[lowKey] + highWeight*property[highKey])/(lowWeight+highWeight);
    } else {
      // found
      return property[time];
    }


}

int CSVParser::getHighestDatapoint() {
    return property.begin()->first;
}

int CSVParser::getLowestDatapoint() {
    return property.end()->first;
}



CSVParser::~CSVParser() {
}

