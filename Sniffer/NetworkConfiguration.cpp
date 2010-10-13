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
	int NetworkConfiguration::userOption = 0;

	NetworkConfiguration::NetworkConfiguration() {
			char errbuf[PCAP_ERRBUF_SIZE];

			if(pcap_findalldevs(&devices, errbuf) == -1)
				printf("Failed getting all devices");
	}

	void NetworkConfiguration::showUserOptions()
	{
		int choice;
		int index = 1;
		pcap_if_t* currDevice;

		printf("Select one of the below interfaces \n");


		for(currDevice = devices; currDevice != NULL; currDevice = currDevice->next, index++)
		{
			printf(" %d. %s\n", index, currDevice->name);
		}

		printf("Enter your choice : ");
		scanf("%d", &choice);
		this->setUserOption(choice);
	}

	void NetworkConfiguration::setUserOption(int option) {
		NetworkConfiguration::userOption = option;
	}

	pcap_if_t* NetworkConfiguration::getSelectedInterface()
	{
		pcap_if_t* currDevice;
		int index = 1;
		for(currDevice = devices; currDevice != NULL; currDevice = currDevice->next, index++)
		{
			if(index == NetworkConfiguration::userOption)
				break;
		}
		return currDevice;
	}

	NetworkConfiguration::~NetworkConfiguration() {
		pcap_freealldevs(devices);
	}
}
