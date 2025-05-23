/*
authors: Ahmed Khaled & Mostafa Abdelrehim
Some of the modules are based on Noxim - the NoC Simulator by the University of Catania
 */

#pragma once

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cassert>
#include <queue>
#include "Flit.h"
#include "Constants.h"


using namespace std;

#define DEFAULT_BUFFER_DEPTH                     16

class Buffer {

public:

	Buffer();

	virtual ~Buffer() {
	} void SetMaxBufferSize(unsigned int bms);	// Set buffer max size (in flits)

	unsigned int GetMaxBufferSize() const;	// Get max buffer size

	unsigned int getCurrentFreeSlots() const;	// free buffer slots

	bool IsFull() const;	// Returns true if buffer is full

	bool IsEmpty() const;	// Returns true if buffer is empty

	void Push(const Flit& flit);	// Push a flit

	Flit Pop();		// Pop a flit

	Flit Head() const;	// Return a copy of the head flit in the buffer
	Flit Tail() const;	// Return a copy of the tail flit in the buffer

	unsigned int Size() const;

	void Clean();

	unsigned int max_buffer_size;

	Flit getElement(const int);

private:

	deque < Flit > buffer;

};

#endif
