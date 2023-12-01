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
    double key = 0;
    double val = 0;
    char sep; //throwaway
    while (file >> line) {
        std::istringstream ss(line);
        ss >> key >> sep >> val;
        property.insert(std::pair<double,double>(key,val));
    }
    return;
}

double CSVParser::getPropertyAtTime(const double time) {
    auto property_value = property.find(time);
    if (property_value == property.end()) {
      // not found, calculate
        double lowWeight = 0,highWeight = 0;
        double lowKey = 0, highKey = 0;
        lowKey = (--property.upper_bound(time))->first;
        highKey = property.upper_bound(time)->first;

        lowWeight = simTime().dbl() - lowKey;
        highWeight = highKey - simTime().dbl();
        last_polled_value = (lowWeight*property[lowKey] + highWeight*property[highKey])/(lowWeight+highWeight);
    } else {
      // found
    last_polled_value = property_value->second;
    }
      return last_polled_value;
    }


int CSVParser::getLowestDatapoint() {
    return property.begin()->first;
}

int CSVParser::getHighestDatapoint() {
    return property.rbegin()->first;
}



CSVParser::~CSVParser() {
}

