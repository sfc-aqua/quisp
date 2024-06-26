/*
 * OrbitalDataParser.h
 *
 *  Created on: Nov 28, 2023
 *      Author: paolo
 */

#pragma once

#include <omnetpp.h>
#include <fstream>
#include <map>

using namespace omnetpp;
using std::string;

class OrbitalDataParser {
 public:
  OrbitalDataParser();
  OrbitalDataParser(const string filename);
  virtual ~OrbitalDataParser();
  double getPropertyAtTime(const double time);
  double getLowestDatapoint();
  double getHighestDatapoint();
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
