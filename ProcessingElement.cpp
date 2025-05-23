/*
authors: Ahmed Khaled & Mostafa Abdelrehim
Some of the modules are based on Noxim - the NoC Simulator by the University of Catania
*/
#include "ProcessingElement.h"

void ProcessingElement::reset() {
	position_cur = coord.id2Coord(local_id);
	local_id_string = to_string(local_id);

	file_to_read = "PktstoSend_Folder/PktstoSend" + local_id_string + ".xls"; // each core has it is own file to grab the packets to send
	//pkts_toWrite.open(file_to_write, ios::app); // the is used if you wanna create different set of packets
	pkts_toRead.open(file_to_read); // open file to read the packets 

	Total_queueDelay = 0; // total queeuing delay of packet received
	Total_Wait = 0; // total waiting time, this is required to clculate average injection rate (injection rate = total sent packets / total waiting time)
	Total_Received = 0;  // total number of packets received
	Total_Transmitted = 0;  // if one packet has more than 1 flit then the count of all flit sent is stored in this variable
	Total_Pkts_Transmitted = 0; // total number of packets sent
	Total_Delay = 0; // total queeuing delay of packet received = Total_queueDelay , it was made to test correctness
	waitingTime = 0; // timecore should wait before sending another packet
	lastClock = 0; // clock of the last flit received
	hops = 0; // total hops 
	hops_x = 0; // total hops in X
	hops_y = 0; // total hops in Y
	hops_z= 0; // total hops in Z

	req_rx = 0; // signal sent from the connected router telling core there is packet coming   
	ack_rx = 0; // signal sent to the connected router telling router it has received the packet
	req_tx = 0; // signal sent to the connected router telling it there is packet coming
	ack_tx = 0; // signal sent from the connected router telling core it has received the packet
	
	flit_temp_rx.clear(flit_temp_rx); //flit_temp_rx temporary variable to store receieved packets
	flit_rx.clear(flit_rx); //flit_rx data bus that carries flit sent to connected router 
	flit_temp_tx.clear(flit_temp_tx); // flit_temp_tx temporary variable to store packets to be transmitted
	flit_tx.clear(flit_tx); //flit_tx data bus that carries flit sent from connected router

	if (local_id < (DIMX) * (DIMY) * DIMZ) // required if you wanna make some cores to send packet. Any core that has lies out of the range will not send  
		End_TX = 0; // the core can send iff End_Tx = 0 (iff = if and only if) 
	else 
		End_TX = 1;
	
	rxState = CHECK_REQ; // reset state of reciving method 
	txState = CHECK_ENDTX; // reset state of transmitting method 

	rxClock = 0; // rxCock = 0 at the start of any new simulation
	txClock = 0; // txCock = 0 at the start of any new simulation

	rxClock_count.clkReset(); // reset the counter of rxClock_count to 0
	txClock_count.clkReset(); // reset the counter of txClock_count to 0
}

void ProcessingElement::rxProcess() {
	rxClock = rxClock_count.count(); // rxProcess is get excuted each clock cycle, rxClock get incremented each clock cycle
	
	if (rxState == CHECK_REQ) {
		if (req_rx == 1) { 

			flit_temp_rx = flit_rx; // if there is a request receive the incoming flit 

			assert(flit_temp_rx.dst_id == local_id); // core cannot sent to itself
			
			ack_rx = 1; // tell the transmitting router that the flit is received 
			
			Total_Received++; // increment total received flitss

			Total_Delay += rxClock - flit_temp_rx.sendTime; // increase total delay
			
			flit_temp_rx.queueDelay += rxClock - flit_temp_rx.storeTime; // total queue delay of a packet is simply the summation of all it queue delay at each hop
			                                                             // delay at each hop is simply the current clock - store time when it is received in the last hop 
			
			Total_queueDelay += flit_temp_rx.queueDelay; // total queue delay of all packets = summation of all queue delays of each packet received  

			hops += (flit_temp_rx.hops); // total hops = summation of all hops of all received packets 

			lastClock = rxClock; // this is useful only if you want to test lastclock count at which the last packet was redeived  (can be ignored)

			rxState = WAIT_REQ_LOW;	// change state 		

			//cout << "1rx CHECK_REQ pe " << local_id << " rx in CHECK_REQ now receiving request req_rx=1 and granting ack_rx=1" << endl;
			//cout << "1rx flit_temp_rx.seq=" << flit_temp_rx.sequence_no << "\tflit_temp_rx.dst=" << flit_temp_rx.dst_id << endl;
			//cout << "/***********************************************/" << endl; ////////////////////////
			//_getch();
		}
	}
	else if (rxState == WAIT_REQ_LOW) {
		if (req_rx == 0) { // if the transmitting router reset its req signal  

			ack_rx = 0; // then reset the ack 

			rxState = CHECK_REQ; // go to the initial state

			//cout << "2rx WAIT_REQ_LOW pe " << local_id << " rx in WAIT_REQ_LOW req_rx=0 and ack_rx=0" << endl;
			//cout << "2rx flit_temp_rx.seq=" << flit_temp_rx.sequence_no << "\tflit_temp_rx.dst=" << flit_temp_rx.dst_id << endl;
			//cout << "/***********************************************/" << endl; ////////////////////////
			//_getch();

		}
	}
}

void ProcessingElement::txProcess()
{
	txClock = txClock_count.count(); // txProcess is get excuted each clock cycle, txClock get incremented each clock cycle
	
	if (waitingTime > 0) { // no sendng before waiting time reduced to 0
		req_tx = 0;
		waitingTime--;
	}
	else{
		if (txState == CHECK_ENDTX) { 

			assert(Total_Transmitted <= TOTAL_SENT_PKT); // to check correctness , no core should send more thna TOTAL_SENT_PKT

			if (!End_TX) {
				flit_temp_tx = nextFlit(); // get new packet
				
				flit_tx = flit_temp_tx; // put hat packet on data bus
				
				req_tx = 1; // put req = 1
				
				txState = WAIT_ACK; // go to the next state

				//cout << "1tx CHECK_ENDTX pe " << local_id << " in tx CHECK_ENDTX sending pkt so put req_tx=1 and wait ack_tx" << endl;
				//cout << "1tx current pkt to be sent in pe is " << flit_temp_tx.sequence_no << endl;
				//cout << "/***********************************************/" << endl; ////////////////////////
				//_getch();
			}
		}
		else if (txState == WAIT_ACK) {
			if (ack_tx == 1) { // if router receives the packet (we knew that if core found ack =1)  

				req_tx = 0; // reset the communication by reseting req back to 0
				
				txState = WAIT_ACK_LOW; // go to the next state

				//cout << "2tx WAIT_ACK pe " << local_id << " ack_tx is now 1 so put req_tx=0 and wait ack_tx to be zero again" << endl; ////////////////////////
				//cout << "2tx current pkt to be sent in pe is " << flit_temp_tx.sequence_no << endl;
				//cout << "/***********************************************/" << endl; ////////////////////////
				//_getch();
			}
		}
		else if (txState == WAIT_ACK_LOW) {
			if (ack_tx == 0) { // if ack = 0, this means the communication is reseted back to the inital state 

				// do some statistics
				Total_Transmitted++; // increase number of sent items (flits) 
				Total_Pkts_Transmitted++; // increment number of sent packets 
				/*in this code packet = 1 flit so both are always equal*/

				if (Total_Transmitted == TOTAL_SENT_PKT) { // if core sent all its assigned packets, then set End_TX 
					End_TX = 1;
					pkts_toRead.close(); // clodw the file we read from
				}

				waitingTime = getRandomInteger(WAITTIME); // set some random integer to wait before sending another packet 

				Total_Wait += waitingTime; // to calculate injection rate 
				assert(waitingTime <= WAITTIME); // check correctness WAITTIME is max waiting time (time here is number of cycles)

				txState = CHECK_ENDTX; // go to the inital state

				//cout << "3tx WAIT_ACK_LOW pe " << local_id << " ack is again 0 " << endl; ////////////////////////
				//cout << "/***********************************************/" << endl; ////////////////////////
				//_getch();
			}
		}	
	}
}

Flit ProcessingElement::nextFlit()
{
	Flit flit;
	/*The following os a simple functiopn that reads a complete row from excel sheet where each celll in this row ius a packet field*/
	string row;
	char *pch, *token;
	if (getline(pkts_toRead, row,'\n'))
	{
		char cstr[1024];
		strcpy(cstr,row.c_str());
		pch = strtok_r(cstr, "\t", &token);
		int counter = 0;
		while (pch != NULL)
		{
			double entry = atof(pch) ;
			if (counter == 0)
				flit.dst_id = entry;
			if (counter == 1)
				flit.payload = entry;
			if (counter == 2)
				flit.queueDelay = entry;
			if (counter == 3)
				flit.sendTime = entry;
			if (counter == 4)
				flit.sequence_no = entry;
			if (counter == 5)
				flit.src_id = entry;
			if (counter == 6)
				flit.storeTime = entry;
			if (counter == 7)
				flit.type = static_cast<FlitType>(int(entry));
		
			pch = strtok_r(NULL, "\t", &token);
			counter++;
		}
	}

	/*if you construct a packet rather than reading it from packet data set in the files you can use the commented liunes in the following*/
	/*in the followin galso some correctness checks*/
	//flit.src_id = local_id;
	assert(flit.src_id == local_id);

	flit.sendTime = txClock;

	assert(flit.sequence_no == getTotal_Transmit());
	//flit.sequence_no = getTotal_Transmit();

	flit.storeTime = txClock; //
	flit.queueDelay = 0.0; //

	//flit.payload = 0;

	//flit.type = HEAD;
	assert(flit.type == HEAD); // since all packet has only 1 flit, then any flit is head flit

	assert(flit.dst_id < DIMX * DIMY * DIMZ); // the dst must be within network
	assert(flit.dst_id != flit.src_id); // any core must send to different core 

	flit.hops = 0;

	position_dst = coord.id2Coord(flit.dst_id); // id2Coord converts id number of the core (local) to coordinates x, y, z
	/*simple way to know how many hops i x, y, z were traveresed by packet - this important for some analysis*/
	hops_x += abs(position_dst.x - position_cur.x); 
	hops_y += abs(position_dst.y - position_cur.y);
	hops_z += abs(position_dst.z - position_cur.z);

	return flit;
}

int ProcessingElement::getTotal_Transmit() {
	return Total_Pkts_Transmitted + local_id * 100000; // this a way to construct unique seral number to each packet 
}

int ProcessingElement::CalcDelay(int start_clock) {
	return rxClock - start_clock; // simply to calculate the delay of any packet subtract the current clock count from the clk count at its transmission
}

int ProcessingElement::getRandomInteger(const int RANGE) { // function to generate unofrm random number 
	const int range_from = 0;
	const int range_to = RANGE;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());// generator(2322); //
	std::uniform_int_distribution<int>  distr(range_from, range_to);

	return distr(generator);

	/*unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();;
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(0.0, double(RANGE));
	return int(distribution(generator));*/
}
