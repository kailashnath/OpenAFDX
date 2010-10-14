/*
 * NetworkConfiguration.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "NetworkConfiguration.h"

namespace network
{
	NetworkConfiguration::NetworkConfiguration()
	: noOfInterfaces(0), userOption(0) {
			char errbuf[PCAP_ERRBUF_SIZE];

			if(pcap_findalldevs(&devices, errbuf) == -1)
				cout << "Failed getting all devices";
	}

	void NetworkConfiguration::showUserOptions()
	{
		int choice;
		int index = 1;
		pcap_if_t* currDevice;

		printf("Select one of the below interfaces \n");


		for(currDevice = devices; currDevice != NULL;
			currDevice = currDevice->next, index++)
		{
			cout << index << "." << currDevice->name << endl;
			noOfInterfaces ++;
		}

		cout << "Enter your choice : ";

		// convert the user entered input to integer
		cin >> dec >> choice;
		this->setUserOption(choice);
	}

	int NetworkConfiguration::setUserOption(int option) {

		if(option > noOfInterfaces)
		{
			cout << "Invalid Option" << endl;
			return -1;
		}

		userOption = option;
		return 0;
	}

	pcap_if_t* NetworkConfiguration::getSelectedInterface()
	{
		if(userOption == 0 || userOption > noOfInterfaces)
		{
			return NULL;
		}

		pcap_if_t* currDevice  = NULL;
		int 	   deviceIndex = 1;

		for(currDevice = devices; currDevice != NULL;
				currDevice = currDevice->next, deviceIndex++)
		{
			if(deviceIndex == userOption)
				break;
		}

		return currDevice;
	}

	NetworkConfiguration::~NetworkConfiguration() {
		pcap_freealldevs(devices);
	}
}
