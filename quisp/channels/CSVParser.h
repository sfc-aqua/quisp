/*
 * CSVParser.h
 *
 *  Created on: Nov 28, 2023
 *      Author: paolo
 */

#ifndef CHANNELS_CSVPARSER_H_
#define CHANNELS_CSVPARSER_H_

#include <omnetpp.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

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
  double getLowestDatavalue();
  double getHighestDatavalue();

  char* getName;

 private:
  std::ifstream file;
  char* name;
  double last_polled_time = -1;
  double last_polled_value = -1;
  std::map<double, double> property;
};

#endif /* CHANNELS_CSVPARSER_H_ */
