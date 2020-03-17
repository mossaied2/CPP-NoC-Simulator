#pragma once
#ifndef __CLOCKCOUNT_H__
#define __CLOCKCOUNT_H__

class ClockCount {
public:
	long double clockCount;

	ClockCount() {
		clockCount = 0;
	}
	
	void clkReset() {
		clockCount = 0;
	}

	double count(){
		return clockCount++;
	}
};

#endif