/*
 * CSVParser.h
 *
 *  Created on: Nov 28, 2023
 *      Author: paolo
 */

#ifndef CHANNELS_CSVPARSER_H_
#define CHANNELS_CSVPARSER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <omnetpp.h>
#include <map>

using namespace omnetpp;
using std::string;

class CSVParser {
public:
    CSVParser();
    CSVParser(const string filename);
    virtual ~CSVParser();
    double getPropertyAtTime(const double time);
    int getLowestDatapoint();
    int getHighestDatapoint();
    char* getName;
private:
    std::ifstream file;
    char* name;
    double last_polled_value;
    std::map<double,double> property;

};

#endif /* CHANNELS_CSVPARSER_H_ */
