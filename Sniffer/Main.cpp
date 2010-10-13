/*
 * Main.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <boost/thread.hpp>

#include "NetworkConfiguration.h"
#include "Sniffer.h"

using namespace std;
using namespace network;

int main(void)
{
	NetworkConfiguration nc;
	nc.showUserOptions();

	Sniffer sf(nc.getSelectedInterface());

	boost::thread workerThread(Sniffer::startSniffing);
	boost::thread monitorSnifferThread(Sniffer::monitorSniffer);
	monitorSnifferThread.join();

	cout << "Completed";
	return -1;
}