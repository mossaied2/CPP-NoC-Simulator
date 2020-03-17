#pragma once
/*
 * Noxim - the NoC Simulator
 *
 * (C) 2005-2010 by the University of Catania
 * For the complete list of authors refer to file ../doc/AUTHORS.txt
 * For the license applied to these sources refer to file ../doc/LICENSE.txt
 *
 * This file contains the declaration of the router
 */

#ifndef __NOXIMROUTER_H__
#define __NOXIMROUTER_H__

#include <math.h>
#include "Buffer.h"
#include "ReservationTable.h"
#include "ClockCount.h"
#include "Coordinate.h"
#include "Constants.h"

using namespace std;

class Router
{
public:

	long double txClock = 0;	// /* input */ The input clock for the PE
	long double rxClock = 0;	// /* input */ The input clock for the PE

	Flit flit_rx[DIRECTIONS];	  	// /*input*/ The input channels (including local one)
	bool req_rx[DIRECTIONS];	  	// /*input*/ The requests associated with the input channels
	bool ack_rx[DIRECTIONS];	  	// /*out*/  The outgoing ack signals associated with the input channels

	Flit flit_tx[DIRECTIONS];   	// /*out*/ The output channels (including local one)
	bool req_tx[DIRECTIONS];	  	// /*out*/ The requests associated with the output channels
	bool ack_tx[DIRECTIONS];	  	// /*input*/ The outgoing ack signals associated with the output channels

	int local_id;     // Unique ID

	Buffer buffer[DIRECTIONS];	 // Buffer for each input channel 

	int txState[DIRECTIONS] = { 0 };
	int rxState[DIRECTIONS] = { 0 };

	RouterArch ROUTER_ARCHITECTURE;
	bool TxFinish = false;

	int roundRobin = 0;

	long double epmty_buffer = 0;

	Router() {
		for (int i = 0; i < DIRECTIONS; i++) {
			ack_rx[i] = 0;
			req_rx[i] = 0;
			req_tx[i] = 0;
			ack_tx[i] = 0;
			buffer[i].SetMaxBufferSize(MinBufferSize);
		}
	}

	Flit flit_temp_tx[DIRECTIONS];
	Flit flit_temp_rx[DIRECTIONS];

	void rxProcess(); // The receiving process
	void txProcess(); // The transmitting process
	void reset();

private:
	ClockCount rxClock_count;
	ClockCount txClock_count;
	ReservationTable reservation_table;

	// performs actual routing + selection
	int route(const Flit&);
};

#endif
