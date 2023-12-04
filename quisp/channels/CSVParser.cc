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
    if (time == last_polled_time) return last_polled_value;
    last_polled_time = time;

    auto u_b = property.upper_bound(time);
    if (u_b == property.end()) {
      return --(u_b)->second;
    }
    if (u_b == property.begin()) {
        return u_b->second;
      }

    auto l_b = u_b; --u_b;
    const double delta = (time - l_b->first)/(u_b->first - l_b->first);
    return delta*u_b->second + (1-delta)*l_b->second;


    }


int CSVParser::getLowestDatapoint() {
    return property.begin()->first;
}

int CSVParser::getHighestDatapoint() {
    return property.rbegin()->first;
}



CSVParser::~CSVParser() {
}

