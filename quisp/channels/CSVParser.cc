/*
 * CSVParser.cc
 *
 *  Created on: Nov 28, 2023
 *      Author: paolo
 */

#include "CSVParser.h"

CSVParser::CSVParser(char* filename) {
    std::istream file = infile(filename);
    char* line;
    int key = 0;
    float val = 0;
    while (file >> line) {
        sscanf(line,"%d,%f",&key,&val);
        property.insert(std::pair<int,float>(key,val));
    }
    return;
}

float CSVParser::getPropertyAtTime(SimTime time) {
    if (property.find(time) == property.end()) {
      // not found
        float lowWeight = 0,highWeight = 0;
        int lowKey = 0, highKey = 0;
        lowKey = property.lower_bound(time);
        highKey = property.upper_bound(time);

        lowWeight = simTime() - lowKey;
        highWeight = highKey - simTime();

        return (lowWeight*property[lowKey] + highWeight*property[highKey])/(lowWeight+highWeight);
    } else {
      // found
      return property[time];
    }


}

CSVParser::~CSVParser() {
}

