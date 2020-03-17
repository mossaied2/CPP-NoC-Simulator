#pragma once

#ifndef __FLIT_H__
#define __FLIT_H__
/*
enum NoximFlitType {
	HEAD, BODY, TAIL
};
*/
#include "Constants.h"

// NoximFlit -- Flit definition
struct Flit {
	int src_id;
	int dst_id;
	FlitType type;		// The flit type (HEAD, BODY, TAIL)
	unsigned long int  sequence_no;		// The sequence number of the flit inside the packet
	unsigned long int  payload;		// Optional payload
	double sendTime; //
	//double queueTime; //
	long double storeTime; //
	long double queueDelay; //

	long double hops;

	inline bool operator ==(const Flit& flit) const {
		return (flit.src_id == src_id && 
				flit.dst_id == dst_id && 
				flit.type == type && 
				flit.sequence_no == sequence_no && 
				flit.payload == payload && 
				flit.sendTime == sendTime && 
				flit.storeTime == storeTime &&
				flit.queueDelay == queueDelay &&
				flit.hops == hops);
	}


	void clear(Flit& flit) {
		flit.src_id = -1;
		flit.dst_id = -1;
		flit.sequence_no = -1;		// The sequence number of the flit inside the packet
		flit.payload = -1;		// Optional payload
		flit.sendTime = -1; //
		flit.storeTime = -1; //
		flit.queueDelay = -1; //
		flit.hops = -1;
	}
}; 

#endif