/*
authors: Ahmed Khaled & Mostafa Abdelrehim
Some of the modules are based on Noxim - the NoC Simulator by the University of Catania
*/
#pragma once

#include "Router.h"

void Router::reset() { // reset to intial state before any simulation run
	
	for (int port = 0; port < DIRECTIONS; port++) { // we have # of DIRECTIONS ports (N, S, E, W, U, D, Local) // each one has its own identical signal
		/*inital state of handshaking signals: req and ack, are all 0 */
		ack_rx[port] = 0;
		req_rx[port] = 0;
		req_tx[port] = 0;
		ack_tx[port] = 0;

		/*clear any data bus before any simulation run*/
		flit_rx[port].clear(flit_rx[port]);
		flit_tx[port].clear(flit_tx[port]);

		/*clear any flit register before any simulation run*/
		flit_temp_rx[port].clear(flit_temp_rx[port]);
		flit_temp_tx[port].clear(flit_temp_tx[port]);

		txClock = 0; // txCock = 0 at the start of any new simulation
		rxClock = 0; // rxCock = 0 at the start of any new simulation

		buffer[port].Clean(); // clean out all the FIFO bufffers

		reservation_table.release(port); // release any reserved port

		rxState[port] = CHECK_BUFFER; //initial state in both receiving and transmitting
		txState[port] = CHECK_BUFFER;

		rxClock_count.clkReset(); // reset the counter of rxClock_count to 0
		txClock_count.clkReset(); // reset the counter of txClock_count to 0
	}
}

void Router::rxProcess() {
	rxClock = rxClock_count.count();

	assert(buffer[LOCAL].max_buffer_size == INFINTE_BUFFER_SIZE);
	for (int inPort = 0; inPort < DIRECTIONS; inPort++) { // do the same stuff on each port so loop is the best way to handle that

		if (rxState[inPort] == CHECK_BUFFER) { // base on buffer status we can acept or reject an incoming request
			
			if (ROUTER_ARCHITECTURE == CONVENTIONAL) {
				if(req_rx[inPort] == 1){ // check if there is a request

					if (!buffer[inPort].IsFull()) { // check buffer if it has at least one free slot

						flit_temp_rx[inPort] = flit_rx[inPort]; // read packet on data bus 

						flit_temp_rx[inPort].queueDelay += rxClock - flit_temp_rx[inPort].storeTime; // increment queu delay
						
						flit_temp_rx[inPort].storeTime = rxClock; //recordstore time of the packet in the current router

						if(inPort != LOCAL)
							flit_temp_rx[inPort].hops++; // increment number of hops

						buffer[inPort].Push(flit_temp_rx[inPort]); // stoer packet in the buffer

						ack_rx[inPort] = 1; //set ack on that port, telling the seding router (or core if port is LOCAL) that the packet is received
						rxState[inPort] = WAIT_REQ_LOW; // go next state

						//cout << "1rx CHECK_BUFFER router " << local_id << " rx received req in clock " << rxClock << endl;
						//cout << "1rx the received pkt is flit_temp_rx.seq=" << flit_temp_rx[inPort].sequence_no << "\tflit_temp_rx.dst=" << flit_temp_rx[inPort].dst_id << endl;
						//cout << "/***********************************************/" << endl; ////////////////////////
						//_getch();
					}
					else {
						rxState[inPort] = CHECK_BUFFER; // stay in the same state if request is not served
					}
				}
			}
			
		}
		else if (rxState[inPort] == WAIT_REQ_LOW) {
			if (req_rx[inPort] == 0) { // if sender reset the request

				ack_rx[inPort] = 0; // reset the ack
				rxState[inPort] = CHECK_BUFFER; // go to initiak state

				//cout << "2rx WAIT_REQ_LOW router " << local_id << " rx in WAIT_REQ_LOW the req is zero again in inPort " << inPort << endl;
				//cout << "2rx the received pkt was flit_temp_rx.seq=" << flit_temp_rx[inPort].sequence_no << "\tflit_temp_rx.dst=" << flit_temp_rx[inPort].dst_id << endl;
				//cout << "/***********************************************/" << endl; ////////////////////////
				//_getch();
			}
		}	
	}
}

void Router::txProcess(){
	txClock = txClock_count.count();

	for (int inPort = 0; inPort < DIRECTIONS; inPort++){
		if (txState[inPort] == CHECK_BUFFER) { // check buffer if it has packet, then proceed and route it
			if (!buffer[inPort].IsEmpty()) { // if there is at least one packet 

				flit_temp_tx[inPort] = buffer[inPort].Head(); // read the buffer head packet  

				int outPort = route(flit_temp_tx[inPort]); // get output port accroding to routing algorithm 

				assert(outPort < DIRECTIONS); // check for correctness 

				if (!reservation_table.isAvailable(outPort)) { // do not use this out port if it is reserved by other inputport
					continue;
				}
				reservation_table.reserve(inPort, outPort); // otherwise reserve this output for that port 

				flit_tx[outPort] = flit_temp_tx[inPort]; // put packet on data bus
				
				req_tx[outPort] = 1; // set request = 1

				txState[inPort] = WAIT_ACK; // go to next state

				//cout << "1tx CHECK_BUFFER router tx CHECK_BUFFER packet to sent" << endl;
				//cout << "1tx pkt to be sent  is flit_temp_tx[inPort].seq=" << flit_temp_tx[inPort].sequence_no << "\tflit_temp_rx.dst=" << flit_temp_tx[inPort].dst_id << endl;
				//cout << "/***********************************************/" << endl; ////////////////////////
				//_getch();
			}
		}
		else if (txState[inPort] == WAIT_ACK) { /////////////////////////////////
			int outPort = reservation_table.getOutputPort(inPort); // get output port reserved to that input port
			if (ack_tx[outPort] == 1) { // if ack coming from that port is 1

				req_tx[outPort] = 0; // reset input port 
				
				txState[inPort] = WAIT_ACK_LOW; // go to next state

				//cout << "2tx WAIT_ACK router tx WAIT_ACK  ack is 1 " << endl;
				//cout << "2tx the pkt sent is flit_temp_tx.seq=" << flit_temp_tx[inPort].sequence_no << "\tlit_temp_tx.dst=" << flit_temp_tx[inPort].dst_id << endl;
				//cout << "/***********************************************/" << endl; ////////////////////////
				//_getch();
			}
		}
		else if (txState[inPort] == WAIT_ACK_LOW) {
			int outPort = reservation_table.getOutputPort(inPort); // get output port reserved to that input port
			if (ack_tx[outPort] == 0) { // if ack coming from that port is 0 (the downstream router resets the handshaking)

				buffer[inPort].Pop(); // remove the packt that just sent from the buffer 

				reservation_table.release(outPort); // release the reservation 

				txState[inPort] = CHECK_BUFFER; // go to inital state

				//cout << "3tx WAIT_ACK_LOW router tx WAIT_ACK_LOW, now ack is 0 again " << endl;
				//cout << "3tx the successfully pkt sent is flit_temp_tx.seq=" << flit_temp_tx[inPort].sequence_no << "\tlit_temp_tx.dst=" << flit_temp_tx[inPort].dst_id << endl;
				//cout << "/***********************************************/" << endl; ////////////////////////
				//_getch();
			}
		}	
	}
}

int Router::route(const Flit & flit)
{ // routing 
    if (flit.dst_id == local_id) // if packet reached destinsation 
		return LOCAL;

	Coord position_curr, position_dest; 
	position_curr.postion = position_curr.id2Coord(local_id); // get coordinates of current core (=ID of current router)
	position_dest.postion = position_dest.id2Coord(flit.dst_id); // get coordinates of curren (=ID of destination router)

	// xyz routing algorithm: 
	if (position_dest.postion.x > position_curr.postion.x)  // x has priority over y and z 
		return EAST;
	if (position_dest.postion.x < position_curr.postion.x)
		return WEST;
	if (position_dest.postion.y > position_curr.postion.y) // y has priority over z
		return NORTH;
	if (position_dest.postion.y < position_curr.postion.y)
		return SOUTH;
	if (position_dest.postion.z > position_curr.postion.z)
		return UP;
	if (position_dest.postion.z < position_curr.postion.z)
		return DOWN;
}

