/*
Authors: Mostafa Abdelrehim
Some of the modules are based on Noxim - the NoC Simulator by the University of Catania
*/
#pragma once

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

//#include <conio.h>
#include <time.h>  
#include <random>
#include <assert.h>
#include <algorithm>
#include <map>
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

#define MinBufferSize 1 
#define DIMX 8 // number of routers in x dimension
#define DIMY 8 // number of routers in y dimension
#define DIMZ 8 // number of routers in z dimension

#define TOTAL_SENT_PKT 1000 // number of packets to be sent by each sender

#define INFINTE_BUFFER_SIZE TOTAL_SENT_PKT // usually local buffer has very big size. 
										   // In theory it is assumed infinte. Since we cannot implemnt infinte 
                                           // size we put it as the max number of packets to be sent so that we are sure 
										   // it will not block any incoming packet same as if it was infinte 

#define NUMBER_OF_SENDERS (DIMX * DIMY * DIMZ)   // all cores can send packets 

#define SKIP_CYCLES 10000 // number of cycles aftyer which the simulation kernel would show the total number of packets received  

/*Each direction is assigned a number*/
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5
#define LOCAL 6

#define DIRECTIONS 7 // total number of directions that a packet can go in 3D network

#define NOT_VALID -1 // an indication in invalid direction

#define NOT_RESERVED -2 // an indication that some output port is not reserved 

#define CHECK_REQ 0 // core rx state

#define CHECK_ENDTX 0 // core tx 1st state
#define WAIT_ACK 1 // core tx 2nd state
#define WAIT_ACK_LOW 2 // core last tx state

//#define DIM_2_CORNERS 4 // how many routers on corners in 2D network
#define DIM_3_CORNERS 8 // how many routers on corners in 3D network

#define CHECK_BUFFER 0 // router tx and rx 1st state
#define WAIT_REQ_LOW 1 // router rx last state

#define WAIT_ACK 1 // router tx 1st state
#define WAIT_ACK_LOW 2 // router tx last state

enum FlitType { // to define flit types
	HEAD, // first flit sent  
	BODY, // any flit in between Head and tail called body
	TAIL // last flit sent
};


enum RouterArch {
	CONVENTIONAL // if we change router architecture we define here new router architecture type
};


#endif

