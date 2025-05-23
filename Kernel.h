/*
authors: Ahmed Khaled & Mostafa Abdelrehim
*/
#pragma once
#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <queue>

#include <math.h>
#include <cmath>
#include <cassert>
#include "Flit.h"
#include "Coordinate.h"
#include "Router.h"
#include "ProcessingElement.h"

class Kernel {
public:

	long double clock;	// /* input */ The input clock
	bool reset;		// /* input */ The reset signal for all modules
	int Total_PKT_Received;
	long double Total_queueDelay = 0;
	long double Total_Delay = 0;
	double Total_received = 0;
	bool TxFinish = true;

	long double Blockings = 0;
	long double resolutionsFlexibility = 0;
	long double resolutionsMainBuffer = 0;
	long double resolutionsTotal = 0;
	long double epmty_buffer = 0;
	long double hops = 0, hops_x = 0, hops_y = 0, hops_z = 0;
	long double PKTinNB = 0, PKTinSB = 0, PKTinEB = 0, PKTinWB = 0, PKTinUB = 0, PKTinDB = 0;
	long double ResolutionNP = 0, ResolutionSP = 0, ResolutionEP = 0, ResolutionWP = 0, ResolutionUP = 0, ResolutionDP = 0;
	long double Pkts_FIRST = 0, Pkts_SECOND = 0, Pkts_THIRD = 0, Pkts_FORTH = 0;
	ClockCount Clockcount;

	vector <Router> router = vector <Router>(DIMX * DIMY * DIMZ);// [DIMX * DIMY] ;// { ROUTER, ROUTER_SEQ, MaxBufferSize }; // /* module */ router
	vector <ProcessingElement> PE = vector <ProcessingElement>(DIMX * DIMY * DIMZ);// [DIMX * DIMY] ;// { ROUTER, ROUTER_SEQ, MaxBufferSize }; // /* module */ router

	// Constructor
	Kernel(){
		TxFinish = true;
		Total_PKT_Received = TOTAL_SENT_PKT *(NUMBER_OF_SENDERS);
		for (int tile = 0; tile < DIMX * DIMY * DIMZ; tile++) {
			router[tile].local_id = tile;
			PE[tile].local_id = tile;
		}
	}

	// Functions
	void RUN(); // The receiving process

private:
	void SET_SIGNALS();
	double getInjectionRate();
	double getAverageThroughput();
	double getAverageDelay();
	void getResults(double AvgIR_DE_TH[], int);
};

#endif
