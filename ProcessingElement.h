/*
authors: Ahmed Khaled & Mostafa Abdelrehim
Some of the modules are based on Noxim - the NoC Simulator by the University of Catania
*/
#pragma once

#ifndef __PROCESSINGELEMENT_H__
#define __PROCESSINGELEMENT_H__

#define FLITS_PER_PKT 1

#include <math.h>
#include <queue>
#include <iostream>
#include <cmath>
#include <cassert>
#include "Flit.h"
#include "Coordinate.h"
#include "ClockCount.h"
#include "Constants.h"

using namespace std;

class ProcessingElement {
public:

	string local_id_string, file_to_read;

	// Constructor
	ProcessingElement() {
		Total_Received = 0;
		Total_Transmitted = 0;
		req_rx = 0;
		ack_rx = 0;
		req_tx = 0;
		ack_tx = 0;
		End_TX = 0;
	}

	ifstream pkts_toRead;
	//ofstream pkts_toWrite; used only to generate new set of packets

	Coord coord;
	Position position_cur, position_dst;

	bool End_TX;

	long double txClock = 0;	// /* input */ The input clock for the PE
	long double rxClock = 0;	// /* input */ The input clock for the PE

	int last_dest_id; // /* input */ not_full signal from queue

	Flit flit_rx;	// /* input */ The input channel
	bool req_rx;	// /* input */ The request associated with the input channel
	bool ack_rx;	// /* out */ The outgoing ack signal associated with the input channel

	Flit flit_tx;	// /* out */ The output channel
	bool req_tx;	// /* out */ The request associated with the output channel
	bool ack_tx;	// /* input */ The outgoing ack signal associated with the output channel

	int local_id;			            // Unique identification number
	int sequence;                       // seq number of packet

	int txState = 0;                    // state machine variables 
	int rxState = 0;                      

	// Functions
	void rxProcess();					// The receiving process
	void txProcess();					// The transmitting process  
	void reset(); // to reset variable before any new simulation

	Flit nextFlit(); // construct and get next flit	
	int CalcDelay(int);	// Take the next flit of the current packet
	int getTotal_Transmit(); // total number of transmitted packets
	long double hops = 0; // total hops packet will take toreach their destinatuons 
	long double hops_x = 0, hops_y = 0, hops_z = 0; // total hops packet will take toreach their destinatuons in eith x, y, or z
	double Total_Received = 0; // total number of received packets 
	int Total_Transmitted = 0; // total tranmitted items (flits) 
	int Total_Pkts_Transmitted = 0; // total packets tranmitted. in this simulator each packet is only 1 flit so Total_Transmitted = Total_Pkts_Transmitted
	long double Total_Delay = 0; // total delay of all packets received 
	long double Total_queueDelay = 0; // total delay of all packets received  Total_queueDelay = Total_Delay. used to check correctness  
	double lastClock = 0; // can be used to calculate speed of the network instead of Total_queueDelay (or Total_Delay)
	int WAITTIME; // max wait time before sending a new packet 

	double waitingTime = 0;	// time in cycles to wait before sending another packet 
	long double Total_Wait = 0; // to calculate injection rate

	ClockCount rxClock_count;
	ClockCount txClock_count;

	Flit flit_temp_rx;
	Flit flit_temp_tx;

	int getRandomInteger(const int);
};

#endif
