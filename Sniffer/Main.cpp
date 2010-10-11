/*
 * Main.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: root
 */

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "NetworkConfiguration.h"
#include "Sniffer.h"

using namespace std;

int main(void)
{
	NetworkConfiguration nc;
	nc.showUserOptions();
	Sniffer sf(nc.getSelectedInterface());
	sf.printInterfaceDetails();
	sf.startSniffing();
	cout << "Done";
	return -1;

}
