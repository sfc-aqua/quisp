/*
 * struct.h
 *
 *  Created on: 2018/03/19
 *      Author: takaakimatsuo
 */

#ifndef MODULES_STRUCT_H_
#define MODULES_STRUCT_H_

typedef struct selfQubitInfo{
     int stationaryQubit_address;
     int node_address;
     int qnic_address;
};

typedef struct entangledQubitInfo{
     int stationaryQubit_address;
     int node_address;
     int qnic_address;
};



#endif /* MODULES_STRUCT_H_ */
