/** \file CSVParser.cc
 *
 *  \brief CSVParser
 *
 *
 *  Quick parser for CSVs, written for csv-based Free-space channels.
 */

#include "CSVParser.h"

CSVParser::CSVParser(const string filename) {
  file.open(filename);
  if (!file.is_open()) throw cRuntimeError("Couldn't find CSV file!");
  string line;
  double key = 0;
  double val = 0;
  char sep;  // throwaway
  while (file >> line) {
    std::istringstream ss(line);
    ss >> key >> sep >> val;
    property.insert(std::pair<double, double>(key, val));
  }
  return;
}

double CSVParser::getPropertyAtTime(const double time) {
  if (time < getLowestDatapoint()) return getLowestDatavalue();
  if (time > getHighestDatapoint()) return getHighestDatavalue();

  // These two first lines are there just to provide mathematically sound results.
  // They should never be used in actual simulation, as they are NOT in any way
  // guaranteed to be accurate.

  if (time != last_polled_time) {
    last_polled_time = time;
    auto u_b = property.upper_bound(time);
    if (u_b == property.end()) {
      last_polled_value = (--u_b)->second;
    } else if (u_b == property.begin()) {
      last_polled_value = u_b->second;
    } else {
      auto l_b = u_b;
      --l_b;
      const double delta = (time - l_b->first) / (u_b->first - l_b->first);
      last_polled_value = delta * u_b->second + (1 - delta) * l_b->second;
    }
  }
  return last_polled_value;
}

int CSVParser::getLowestDatapoint() { return property.begin()->first; }

int CSVParser::getHighestDatapoint() { return property.rbegin()->first; }

double CSVParser::getLowestDatavalue() { return property.begin()->second; }

double CSVParser::getHighestDatavalue() { return property.rbegin()->second; }

CSVParser::~CSVParser() {}
