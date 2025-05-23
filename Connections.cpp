/*
authors: Ahmed Khaled & Mostafa Abdelrehim
Some of the modules are based on Noxim - the NoC Simulator by the University of Catania
*/
#include "Kernel.h"

void Kernel::SET_SIGNALS() {
	// First middle router that has 4 neighbor routers connections 
	Coord coord;
	Position position;

	// if DIMZ > 1 
	if (DIMX > 1 && DIMY > 1 && DIMZ > 1) { // min is 2x2x2
		assert(DIMX > 1 || DIMY > 1 || DIMZ > 1);
	    // 1st middle routers that has 6 neighbor routers connections" << endl;
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y == 0 || position.y == DIMY - 1 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.x > 0);
			assert(position.y > 0);
			assert(position.z > 0);
			assert(position.x < DIMX - 1);
			assert(position.y < DIMY - 1);
			assert(position.z < DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/

		// 2nd routers that has 5 neighbors 

		// x = 0 middle tiles (no west neighbors, i.e. [rp - 1])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "2 x = 0 middle tiles (no west neighbors, i.e. [rp - 1])" << endl;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x > 0 || position.y == 0 || position.y == DIMY - 1 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			//cout << "rp=" << rp << " x=" << position.x << endl;
			assert(position.x == 0);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// x = DIMX - 1 middle tiles (no east neighbors, i.e. [rp + 1])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "3 x = DIMX - 1 middle tiles (no east neighbors, i.e. [rp + 1])" << endl;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();

			position = coord.id2Coord(rp);
			if (position.x < DIMX - 1 || position.y == 0 || position.y == DIMY - 1 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			assert(position.x == DIMX - 1);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// y = 0 middle tiles (no south neighbors, i.e. [rp - DIMX])
		for (int rp = 0; rp < DIMX * DIMX * DIMZ; rp++) {
			//cout << "4 y = 0 middle tiles (no south neighbors, i.e. [rp - DIMX])" << endl;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y > 0 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == 0);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			//
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			//
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			//
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			//
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			///
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			///
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			///
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			///
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			///
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			///
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y < DIMY - 1 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == DIMY - 1);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// z = 0 middle tiles (no down neighbors, i.e. [rp - DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y == 0 || position.y == DIMY - 1 || position.z > 0)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z == 0);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}
		/*****************************************************************************************************/

		// z = DIMZ - 1 middle tiles (no up neighbors, i.e. [rp + DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y == 0 || position.y == DIMY - 1 || position.z < DIMZ - 1)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z == DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/

		// 3rd (a) routers that has 4 neighbours 

		// y = 0 and x = 0 middle tiles (no west or south neighbors, i.e. [rp - 1] and [rp - DIMX])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x > 0 || position.y > 0 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			assert(position.x == 0);
			assert(position.y == 0);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}
		/*****************************************************************************************************/

		// y = 0 and x = DIMX - 1 middle tiles (no east or south neighbors, i.e. [rp + 1] and [rp - DIMX])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x < DIMX - 1 || position.y > 0 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			assert(position.x == DIMX - 1);
			assert(position.y == 0);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// y = DIMY - 1 and x = DIMX - 1 middle tiles (no east or north neighbors, i.e. [rp + 1] and [rp + DIMX])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x < DIMX - 1 || position.y < DIMY - 1 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			assert(position.x == DIMX - 1);
			assert(position.y == DIMY - 1);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// y = DIMY - 1 and x = 0 middle tiles (no west or north neighbors, i.e. [rp - 1] and [rp + DIMX])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x > 0 || position.y < DIMY - 1 || position.z == 0 || position.z == DIMZ - 1)
				continue;
			assert(position.x == 0);
			assert(position.y == DIMY - 1);
			assert(position.z > 0);
			assert(position.z < DIMZ - 1);

			//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/

		// 3rd (b) routers that has 4 neighbours 

		// z = 0 and y = 0 middle tiles (no down or south neighbors, i.e. [rp - DIMX] and [rp - DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y > 0 || position.z > 0)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == 0);
			assert(position.z == 0);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// z = 0 and y = DIMY - 1 middle tiles (no down or north neighbors, i.e. [rp + DIMX] and [rp - DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y < DIMY - 1 || position.z > 0)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == DIMY - 1);
			assert(position.z == 0);

			//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// z = 0 and x = DIMX - 1 middle tiles (no down or east neighbors, i.e. [rp + 1] and [rp - DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);

			if (position.x < DIMX - 1 || position.y == 0 || position.y == DIMY - 1 || position.z > 0)
				continue;
			assert(position.x == DIMX - 1);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z == 0);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/

		// z = 0 and x = 0 middle tiles (no down or west neighbors, i.e. [rp - 1] and [rp - DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);

			if (position.x > 0 || position.y == 0 || position.y == DIMY - 1 || position.z > 0)
				continue;
			assert(position.x == 0);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z == 0);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/

		// 3rd (c) routers that has 4 neighbours 

		// z = DIMZ - 1 and y = 0 middle tiles (no up or south neighbors, i.e. [rp - DIMX] and [rp + DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y > 0 || position.z < DIMZ - 1)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == 0);
			assert(position.z == DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}
		/*****************************************************************************************************/

		// z = DIMZ - 1 and y = DIMY - 1 middle tiles (no up or north neighbors, i.e. [rp + DIMX] and [rp + DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y < DIMY - 1 || position.z < DIMZ - 1)
				continue;
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == DIMY - 1);
			assert(position.z == DIMZ - 1);

			//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}
		/*****************************************************************************************************/

		// z = DIMZ - 1 and x = 0 middle tiles (no up or west neighbors, i.e. [rp - 1] and [rp + DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);
			if (position.x > 0 || position.y == 0 || position.y == DIMY - 1 || position.z < DIMZ - 1)
				continue;
			assert(position.x == 0);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z == DIMZ - 1);
 
			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}
		/*****************************************************************************************************/

		// z = DIMZ - 1 and x = DIMX - 1 middle tiles (no up or east neighbors, i.e. [rp + 1] and [rp + DIMX * DIMY])
		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			//cout << "5 y = DIMY - 1 middle tiles (no north neighbors, i.e. [rp + DIMX])" << endl;
			//cout << "rp=" << rp << endl;
			//_getch();
			
			position = coord.id2Coord(rp);

			if (position.x < DIMX - 1 || position.y == 0 || position.y == DIMY - 1 || position.z < DIMZ - 1)
				continue;
			assert(position.x == DIMX - 1);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);
			assert(position.z == DIMZ - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			////
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			////
			PE[rp].req_rx = router[rp].req_tx[LOCAL];

			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			////
			//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
			router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
			////
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;

			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
			router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			////
			//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
			router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
			////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}


		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/


		// 4th corners of the cube
		int CORNERS_IDs[DIM_3_CORNERS] = { 0,						(DIMZ - 1) * DIMX * DIMY,
								   DIMX - 1,				(DIMX - 1) + (DIMZ - 1) * DIMX * DIMY,
								   DIMX * (DIMY - 1),       (DIMX * (DIMY - 1)) + (DIMZ - 1) * DIMX * DIMY,
								   DIMX * DIMY - 1,         (DIMX * DIMY - 1) + (DIMZ - 1) * DIMX * DIMY };

		for (int rp = 0; rp < DIMX * DIMY * DIMZ; rp++) {
			
			position = coord.id2Coord(rp);

			// x=0,y=0,z=0 corner router no south, west, or down
			//cout << "x=0,y=0 corner router no south or west" << endl;
			if (position.x == 0 && position.y == 0 && position.z == 0) {
				router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// x=DIMX-1,y=0,z=0 corner router no south, east or down
			if (position.x == DIMX - 1 && position.y == 0 && position.z == 0) {
				router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// x=0,y=DIMY-1,z=0 corner router no north, west, down
			//cout << "x=0,y=DIMY-1 corner router no north or west" << endl;
			if (position.x == 0 && position.y == DIMY - 1 && position.z == 0) {
				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// x=DIMX-1,y=DIMY-1,z=0 corner router no north, east, or down
			//cout << "x=DIMX-1,y=DIMY-1 corner router no north or east" << endl;
			if (position.x == DIMX - 1 && position.y == DIMY - 1 && position.z == 0) {
				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/
			/*****************************************************************************************************/
			/*****************************************************************************************************/
			/*****************************************************************************************************/
			/*****************************************************************************************************/
			/*****************************************************************************************************/
			/*****************************************************************************************************/
			/*****************************************************************************************************/

			// x=0,y=0,z=DIMZ-1 corner router no south, west, or up
			//cout << "x=0,y=0 corner router no south or west" << endl;
			if (position.x == 0 && position.y == 0 && position.z == DIMZ - 1) {
				router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// x=DIMX-1,y=0,z=DIMZ - 1 corner router no south, east or up
			if (position.x == DIMX - 1 && position.y == 0 && position.z == DIMZ - 1) {
				router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// x=0,y=DIMY-1,z=DIMZ - 1 corner router no north, west, up
			//cout << "x=0,y=DIMY-1 corner router no north or west" << endl;
			if (position.x == 0 && position.y == DIMY - 1 && position.z == DIMZ - 1) {
				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// x=DIMX-1,y=DIMY-1,z=DIMZ-1 corner router no north, east, or up
			//cout << "x=DIMX-1,y=DIMY-1 corner router no north or east" << endl;
			if (position.x == DIMX - 1 && position.y == DIMY - 1 && position.z == DIMZ - 1) {
				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				router[rp - 1 * DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				////
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];

				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				router[rp - 1 * DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				////
				PE[rp].req_rx = router[rp].req_tx[LOCAL];

				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				//
				//router[rp].req_rx[UP] = router[rp + 1 * DIMX * DIMY].req_tx[DOWN];
				router[rp].req_rx[DOWN] = router[rp - 1 * DIMX * DIMY].req_tx[UP];
				////
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;

				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				//
				//router[rp].ack_tx[UP] = router[rp + 1 * DIMX * DIMY].ack_rx[DOWN];
				router[rp].ack_tx[DOWN] = router[rp - 1 * DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;

				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				//
				//router[rp + 1 * DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				router[rp - 1 * DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				//
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];

				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//
				//router[rp].flit_rx[UP] = router[rp + 1 * DIMX * DIMY].flit_tx[DOWN];
				router[rp].flit_rx[DOWN] = router[rp - 1 * DIMX * DIMY].flit_tx[UP];
				////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}
		}
	}

	// 5th routers with no up or down neigbors
	// DIMZ = 0 (no up or down)
	if (DIMZ == 1 && DIMX > 1 && DIMY > 1) { // min size 2x2
		// middle routers with 4 neighbours
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y == 0 || position.y == DIMY - 1)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.x > 0);
			assert(position.y > 0);
			assert(position.x < DIMX - 1);
			assert(position.y < DIMY - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		// middle routers with no west (x = 0 , y > 0 and y < DIMY - 1)
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			position = coord.id2Coord(rp);
			if (position.x > 0 || position.y == 0 || position.y == DIMY - 1)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.x == 0);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		// middle routers with no east (x = DIMX - 1 , y > 0 and y < DIMY - 1)
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			position = coord.id2Coord(rp);
			if (position.x < DIMX - 1 || position.y == 0 || position.y == DIMY - 1)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.x == DIMX - 1);
			assert(position.y > 0);
			assert(position.y < DIMY - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		// middle routers with no south (y = 0 , x > 0 and x < DIMX - 1)
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y > 0)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == 0);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		// middle routers with nonorth (y = DIMY - 1 , x > 0 and x < DIMX - 1)
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1 || position.y < DIMY - 1)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.x > 0);
			assert(position.x < DIMX - 1);
			assert(position.y == DIMY - 1);

			//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/

			// corners 
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			position = coord.id2Coord(rp);
			// 1) no up, down, west, and south -> x = 0 and y = 0
			if (position.x == 0 && position.y == 0) {
				//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
				//_getch();
				assert(position.x == 0);
				assert(position.y == 0);

				router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/
			// 2) no up, down, east, and south -> x = DIMX - 1 and y = 0
			if (position.x == DIMX - 1 && position.y == 0) {
				//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
				//_getch();
				assert(position.x == DIMX - 1);
				assert(position.y == 0);

				router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/
			// 3) no up, down, west, and north -> x = 0 and y = DIMY - 1
			if (position.x == 0 && position.y == DIMY - 1) {
				//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
				//_getch();
				assert(position.x == 0);
				assert(position.y == DIMY - 1);

				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/
			// 4) no up, down,east, and north -> x = DIMX - 1 and y = DIMY - 1
			if (position.x == DIMX - 1 && position.y == DIMY - 1) {
				//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
				//_getch();
				assert(position.x == DIMX - 1);
				assert(position.y == DIMY - 1);

				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}
		}
	}

	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/

	// 6th routers with no up, down, west, or east neigbors
	if (DIMZ == 1 && DIMX == 0 && DIMY > 1) {
		// middle routers with 2 neighbours
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			position = coord.id2Coord(rp);
			if (position.y == 0 || position.y == DIMY - 1)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.y > 0);
			assert(position.y < DIMY - 1);

			router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		/*****************************************************************************************************/
		/*****************************************************************************************************/
		/*****************************************************************************************************/

		// corners 
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			position = coord.id2Coord(rp);
			// no south
			if (position.y == 0) {
				router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// no north
			if (position.y == DIMY - 1) {
				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}
		}
	}


	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/

	// 7th router with no  up, down, north, or south neigbors
	if (DIMZ == 1 && DIMY == 0 && DIMX > 1) {
		// middle routers with 2 neighbours
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			//cout << "1 First middle router that has 4 neighbor routers connections" << endl;
			position = coord.id2Coord(rp);
			if (position.x == 0 || position.x == DIMX - 1)
				continue;
			//cout << "rp=" << rp << "\trp.x=" << coord.id2Coord(rp).x << "\trp.y=" << coord.id2Coord(rp).y << endl;
			//_getch();
			assert(position.x > 0);
			assert(position.x < DIMX - 1);

			//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
			//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
			router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
			router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
			///
			//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
			//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
			///
			PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
			//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
			router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
			router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
			///
			//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
			//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
			///
			PE[rp].req_rx = router[rp].req_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
			//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
			router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
			router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
			///
			//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
			//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
			///
			router[rp].req_rx[LOCAL] = PE[rp].req_tx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
			//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
			router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
			router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
			////
			//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
			//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
			////
			router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
			//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
			router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
			router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
			////
			//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
			//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
			////
			PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
			//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
			//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
			router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
			router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
			//////
			//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
			//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
			//////
			router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
		}

		// corners 
		for (int rp = 0; rp < DIMX * DIMY; rp++) {
			position = coord.id2Coord(rp);
			// no west
			if (position.x == 0) {
				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				//router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				//router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				//router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				//router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				//router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				//router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}

			/*****************************************************************************************************/

			// no east
			if (position.x == DIMX - 1) {
				//router[rp + DIMX].ack_tx[SOUTH] = router[rp].ack_rx[NORTH];
				//router[rp - DIMX].ack_tx[NORTH] = router[rp].ack_rx[SOUTH];
				//router[rp + 1].ack_tx[WEST] = router[rp].ack_rx[EAST];
				router[rp - 1].ack_tx[EAST] = router[rp].ack_rx[WEST];
				///
				//router[rp + DIMX * DIMY].ack_tx[DOWN] = router[rp].ack_rx[UP];
				//router[rp - DIMX * DIMY].ack_tx[UP] = router[rp].ack_rx[DOWN];
				///
				PE[rp].ack_tx = router[rp].ack_rx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].req_rx[SOUTH] = router[rp].req_tx[NORTH];
				//router[rp - DIMX].req_rx[NORTH] = router[rp].req_tx[SOUTH];
				//router[rp + 1].req_rx[WEST] = router[rp].req_tx[EAST];
				router[rp - 1].req_rx[EAST] = router[rp].req_tx[WEST];
				///
				//router[rp + DIMX * DIMY].req_rx[DOWN] = router[rp].req_tx[UP];
				//router[rp - DIMX * DIMY].req_rx[UP] = router[rp].req_tx[DOWN];
				///
				PE[rp].req_rx = router[rp].req_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].req_rx[NORTH] = router[rp + DIMX].req_tx[SOUTH];
				//router[rp].req_rx[SOUTH] = router[rp - DIMX].req_tx[NORTH];
				//router[rp].req_rx[EAST] = router[rp + 1].req_tx[WEST];
				router[rp].req_rx[WEST] = router[rp - 1].req_tx[EAST];
				///
				//router[rp].req_rx[UP] = router[rp + DIMX * DIMY].req_tx[DOWN];
				//router[rp].req_rx[DOWN] = router[rp - DIMX * DIMY].req_tx[UP];
				///
				router[rp].req_rx[LOCAL] = PE[rp].req_tx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].ack_tx[NORTH] = router[rp + DIMX].ack_rx[SOUTH];
				//router[rp].ack_tx[SOUTH] = router[rp - DIMX].ack_rx[NORTH];
				//router[rp].ack_tx[EAST] = router[rp + 1].ack_rx[WEST];
				router[rp].ack_tx[WEST] = router[rp - 1].ack_rx[EAST];
				////
				//router[rp].ack_tx[UP] = router[rp + DIMX * DIMY].ack_rx[DOWN];
				//router[rp].ack_tx[DOWN] = router[rp - DIMX * DIMY].ack_rx[UP];
				////
				router[rp].ack_tx[LOCAL] = PE[rp].ack_rx;
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp + DIMX].flit_rx[SOUTH] = router[rp].flit_tx[NORTH];
				//router[rp - DIMX].flit_rx[NORTH] = router[rp].flit_tx[SOUTH];
				//router[rp + 1].flit_rx[WEST] = router[rp].flit_tx[EAST];
				router[rp - 1].flit_rx[EAST] = router[rp].flit_tx[WEST];
				////
				//router[rp + DIMX * DIMY].flit_rx[DOWN] = router[rp].flit_tx[UP];
				//router[rp - DIMX * DIMY].flit_rx[UP] = router[rp].flit_tx[DOWN];
				////
				PE[rp].flit_rx = router[rp].flit_tx[LOCAL];
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////
				//router[rp].flit_rx[NORTH] = router[rp + DIMX].flit_tx[SOUTH];
				//router[rp].flit_rx[SOUTH] = router[rp - DIMX].flit_tx[NORTH];
				//router[rp].flit_rx[EAST] = router[rp + 1].flit_tx[WEST];
				router[rp].flit_rx[WEST] = router[rp - 1].flit_tx[EAST];
				//////
				//router[rp].flit_rx[UP] = router[rp + DIMX * DIMY].flit_tx[DOWN];
				//router[rp].flit_rx[DOWN] = router[rp - DIMX * DIMY].flit_tx[UP];
				//////
				router[rp].flit_rx[LOCAL] = PE[rp].flit_tx;
			}
		}

	}

	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
	/*****************************************************************************************************/
}
