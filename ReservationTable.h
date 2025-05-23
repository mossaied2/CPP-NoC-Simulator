/*
authors: Ahmed Khaled & Mostafa Abdelrehim
Some of the modules are based on Noxim - the NoC Simulator by the University of Catania
*/
#pragma once


#ifndef __RESERVATIONTABLE_H__
#define __RESERVATIONTABLE_H__

#include <cassert>
#include <vector>
#include <iostream>
#include "Constants.h"

using namespace std;

class ReservationTable {
public:

	ReservationTable();

	// Clear reservation table
	void clear();

	// check if port_out is reservable
	bool isAvailable(const int port_out) const;

	// Connects port_in with port_out. Asserts if port_out is reserved
	void reserve(const int port_in, const int port_out);

	// Releases port_out connection. 
	// Asserts if port_out is not reserved or not valid
	void release(const int port_out);

	// Returns the output port connected to port_in.
	int getOutputPort(const int port_in) const;

	// Makes output port no longer available for reservation/release
	void invalidate(const int port_out);

private:
	
	vector < int >rtable;	// reservation vector: rtable[i] gives the input
   // port whose output port 'i' is connected to
};

#endif
