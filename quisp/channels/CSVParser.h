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


class CSVParser {
public:
    CSVParser(char* filename);
    virtual ~CSVParser();
    float getPropertyAtTime(const SimTime& time);
    char* getName;
private:
    char* name;
    std::map<int,float> property;

};

#endif /* CHANNELS_CSVPARSER_H_ */
