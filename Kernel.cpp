/*
Authors: Mostafa Abdelrehim
*/

#include "Kernel.h"

using namespace std;

void Kernel::RUN() {
	ofstream TotalResultFile;

	/* Max time in cycles between successive packets */
	const int TimeBtwnPKTs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,	10,	12, 14, 16, 18, 20,	40,	60 };
	int TimeBtwnPKTsSize = sizeof(TimeBtwnPKTs) / sizeof(TimeBtwnPKTs[0]); // size of the TimeBtwnPKTs array

	/* Buffer sizes */
	const int BufferSizes[] = { 1, 2, 4 };
	int BufferSizesSize = sizeof(BufferSizes) / sizeof(BufferSizes[0]); // size of the BufferSizes array
	
	/* tyoe of router used in simulation */
	const RouterArch ARCH[] = { CONVENTIONAL };  
	int ARCHSize = sizeof(ARCH) / sizeof(ARCH[0]); // size of the ARCH array 

	/* loop over router architectures */
	for (int routerArch_it = 0; routerArch_it < ARCHSize; routerArch_it++){
		RouterArch routerArch = ARCH[routerArch_it];

		/* For any change in  router arch */
		/* let the router know the arch to know how to operate in different situations */
		for (int tile = 0; tile < DIMX * DIMY * DIMZ; tile++) {
			router[tile].ROUTER_ARCHITECTURE = routerArch;
		}

		/* loop over different buffer sizes*/
		for (int newSize = 0; newSize < BufferSizesSize; newSize++){
			
			/* For any change in buyffer */
			/* let the buffers know */
			for (int tile = 0; tile < DIMX * DIMY * DIMZ; tile++) {
				for (int port = 0; port < DIRECTIONS; port++){ // define the buffer size for port
					if(port == LOCAL)
						router[tile].buffer[port].SetMaxBufferSize(INFINTE_BUFFER_SIZE);
					else
						router[tile].buffer[port].SetMaxBufferSize(BufferSizes[newSize]);
				}
			}


			/*writing different paramters of the current simulation run to result file*/
			string strMaxBufferSize = to_string(BufferSizes[newSize]);
			string result = "Results_BufSize" + strMaxBufferSize + "_UniRan_ZYXbuffering.csv";
			TotalResultFile.open(result, ios::app);
			TotalResultFile << "ARCH " << ",TimeBtwnPKTs " << ",Avg IR " << ",Avg DE " << ",Avg TH " << ",Avg QuDe "
				<< ",Total Queue Delay is " << ",Total delay " << ",Last CLK "
				<< ", hops " << ", hops_x" << ", hops_y" << ", hops_z"
				<< endl;


			/* loop over max time between packets*/
			for (int ir = 0; ir < TimeBtwnPKTsSize; ir++) { 

				int SendInterval = TimeBtwnPKTs[ir];
				
				// reseting 
				clock = 0;
				Total_received = 0;
				Total_Delay = 0;
				for (int tile = 0; tile < DIMX * DIMY * DIMZ; tile++) {
					Clockcount.clkReset(); //reset clock device
					router[tile].reset(); // reset routers
					PE[tile].reset(); // reset cores
					PE[tile].WAITTIME = (2 * SendInterval + 1); // define new time between packets (new injection rate)
				}
				
				while (true) { // run simulation under new parameters until all packets are received 

					/* The folowing is the way we model concurrency in hardware */
					/* At each new clock cycle (clock count) all hardware modules run concurrently so in this model */
					/* we first increase clock count then run serislly all the modules as if they are running concurrently */
					clock = Clockcount.count();
					for (int tile = 0; tile < DIMX * DIMY * DIMZ; tile++) {
						router[tile].rxProcess();
						router[tile].txProcess();
						PE[tile].rxProcess();
						PE[tile].txProcess();
					}

					//SET_SIGNALS is a function that transfer signals between neigbor routers
					// at each clock cycle (new clk count) some signals (req, ack, flit) that connect different router/cores
					// chnages by sender/receivers so the other part of the handshalke should see this change in the next clock cycle
					// we do that by SET_SIGNALS function
					SET_SIGNALS();

					Total_received = 0;
					Total_Delay = 0;
					Total_queueDelay = 0;
					hops = 0; hops_x = 0; hops_y = 0; hops_z = 0;
					
					for (int tile = 0; tile < DIMY * DIMX * DIMZ; tile++) {
						Total_received += PE[tile].Total_Received;
						Total_Delay += PE[tile].Total_Delay;
						Total_queueDelay += PE[tile].Total_queueDelay;
						hops += PE[tile].hops;
						hops_x += PE[tile].hops_x;
						hops_y += PE[tile].hops_y;
						hops_z += PE[tile].hops_z;
					}

					assert(Total_received <= Total_PKT_Received);
					unsigned long int clock_ = clock;
				
					if (clock_ % (SKIP_CYCLES) == 0 && clock >= 1) {
						cout << fixed << setprecision(10) << "Total_Received=" << Total_received << " Total_Delay=" << Total_Delay << " Total_QueueDelay=" << Total_queueDelay << " clock=" << clock << endl;
					}

					TxFinish = true;
					for (int pe = 0; pe < DIMX * DIMY * DIMZ; pe++) {
						TxFinish = TxFinish & PE[pe].End_TX;
					}

					for (int pe = 0; pe < DIMX * DIMY * DIMZ; pe++) {
						router[pe].TxFinish = TxFinish;
					}

					if (TxFinish) {

						if (Total_received == Total_PKT_Received)
						{
							// calculate average injection rate 
							double AvgIR_DE_TH[4] = { 0 };
							getResults(AvgIR_DE_TH, SendInterval);

							cout << fixed << setprecision(5) 
								<< "Simulation finished successfully with total recieved packets = " << Total_received << endl
								<< "ARCH is " << routerArch << endl
								<< "Max Buffer Size is " << BufferSizes[newSize] << endl
								<< "TimeBtwnPKTs is " << SendInterval << endl
								<< "Avg IR is " << AvgIR_DE_TH[0] << endl
								<< "Avg DE is " << AvgIR_DE_TH[1] << endl
								<< "Avg TH is " << AvgIR_DE_TH[2] << endl
								<< "Avg QuDe is " << AvgIR_DE_TH[3] << endl
								<< "Total delay is " << Total_Delay << endl
								<< "Total queue Delay is " << Total_queueDelay << endl
								
								<< "hops " << hops << endl
								<< "hops_x " << hops_x << endl
								<< "hops_y " << hops_y << endl
								<< "hops_z " << hops_z << endl
								<< "sum hops_x,y,z=" << hops_x + hops_y + hops_z << endl
								
								<< "Current CLK " << clock << endl;
							
							TotalResultFile << routerArch << "," << SendInterval << "," << AvgIR_DE_TH[0] << "," << AvgIR_DE_TH[1]
								<< "," << AvgIR_DE_TH[2] << "," << AvgIR_DE_TH[3]
								<< "," << Total_queueDelay << "," << Total_Delay << "," << clock
								<< hops << ","
								<< hops_x << "," << hops_y << "," << hops_z << ","
								<< endl;

							break; // if all packets are received break the infinte loop 
						}
					}
				}
			}
			TotalResultFile.close(); //  close the result file
		}
	}
}

void Kernel::getResults(double AvgIR_DE_TH[], const int SendInterval) {

	long double IRs[DIMX * DIMY * DIMZ] = { 0.0 };
	long double Delays[DIMX * DIMY * DIMZ] = { 0.0 };
	long double THs[DIMX * DIMY * DIMZ] = { 0.0 };
	long double Queueing[DIMX * DIMY * DIMZ] = { 0.0 };

	long double sum_IR = 0;
	long double sum_TH = 0;
	long double sum_DE = 0;
	long double sum_QU = 0;

	for (int pe = 0; pe < DIMX * DIMY * DIMZ; pe++) {
		
		long double TOTAL_SENT_PKT_ = TOTAL_SENT_PKT;
		long double Total_Wait_ = PE[pe].Total_Wait;
		long double lastClock_ = PE[pe].lastClock;
		long double Total_Received_ = PE[pe].Total_Received;
		long double Total_Delay_ = PE[pe].Total_Delay;
		long double Total_queueDelay_ = PE[pe].Total_queueDelay;

		IRs[pe] = TOTAL_SENT_PKT_ / Total_Wait_;
		sum_IR += IRs[pe];

		THs[pe] = Total_Received_ / lastClock_;
		sum_TH += THs[pe];

		Delays[pe] = Total_Delay_ / Total_Received_;
		sum_DE += Delays[pe];

		Queueing[pe] = Total_queueDelay_ / Total_Received_;
		sum_QU += Queueing[pe];
	}

	AvgIR_DE_TH[0] = sum_IR / double(DIMX * DIMY * DIMZ);
	AvgIR_DE_TH[1] = sum_DE / double(DIMX * DIMY * DIMZ);
	AvgIR_DE_TH[2] = sum_TH / double(DIMX * DIMY * DIMZ);
	AvgIR_DE_TH[3] = sum_QU / double(DIMX * DIMY * DIMZ);
}

// To calculate throughput (# packets reeived / cycle) per core
double Kernel::getAverageThroughput() {
	long double THs[DIMX * DIMY * DIMZ] = { 0.0 };
	double sum = 0;
	for (int pe = 0; pe < DIMX * DIMY * DIMZ; pe++) {
		cout << "PE[" << pe << "] Total PKTs Received = " << PE[pe].Total_Received
			<< "\t Last CLK Count = " << PE[pe].lastClock
			<< "\t Avg Throughput = " << double(PE[pe].Total_Received) / double(PE[pe].lastClock) << endl;
		THs[pe] = double(PE[pe].Total_Received) / double(PE[pe].lastClock);
		sum += THs[pe];
	}

	double AvgThroughput = sum / double(DIMX * DIMY * DIMZ);

	return AvgThroughput;
}

// To calculate average delay per packet in each core
double Kernel::getAverageDelay() {
	long double Delays[DIMX * DIMY * DIMZ] = { 0.0 };
	double sum = 0;
	for (int pe = 0; pe < DIMX * DIMY * DIMZ; pe++) {
		cout << "PE[" << pe << "] Total PKTs Received = " << PE[pe].Total_Received
			<< "\t Last Total Delay = " << PE[pe].Total_Delay
			<< "\t Avg Delay = " << double(PE[pe].Total_Delay) / double(PE[pe].Total_Received) << endl;
		Delays[pe] = double(PE[pe].Total_Delay) / double(PE[pe].Total_Received);
		sum += Delays[pe];
	}

	double AvgDelay = sum / double(DIMX * DIMY * DIMZ);

	return AvgDelay;
}

