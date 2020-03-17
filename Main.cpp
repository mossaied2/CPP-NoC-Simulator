#pragma once
#include <iostream>
#include "Kernel.h"
using namespace std;


//ofstream dst8, dst368, dst191, dst316, dst205, dst343, dst496, dst491;

int main() {
//	_setmaxstdio(4096); // set max concurrent file handles to 2048 (default is 512) 
	Kernel kernel;
	// start simulation 
	kernel.RUN();
	
	cout << "Hello World" << endl;
	
	return 0;
}
