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
	: _noOfInterfaces(0), _userOption(0) {
			char errbuf[PCAP_ERRBUF_SIZE];

			if(pcap_findalldevs(&_devices, errbuf) == -1)
				cout << "Failed getting all devices";
	}

	void NetworkConfiguration::showUserOptions()
	{
		int choice;
		int index = 1;
		pcap_if_t* currDevice;

		cout << "Select one of the below interfaces" << endl;

		for(currDevice = _devices; currDevice != NULL;
			currDevice = currDevice->next, index++)
		{
			cout << index << "." << currDevice->name << endl;
			_noOfInterfaces ++;
		}

		cout << "Enter your choice : ";

		// convert the user entered input to integer
		cin >> dec >> choice;

		this->setUserOption(choice);
	}

	void NetworkConfiguration::setUserOption(int option) {

		if(0 == option || option > _noOfInterfaces)
		{
			cout << "Invalid Option" << endl;
			return;
		}

		_userOption = option;
	}

	bool NetworkConfiguration::isUserOptionValid()
	{
		if(_userOption == 0 || _userOption > _noOfInterfaces)
		{
			return false;
		}

		return true;
	}

	pcap_if_t* NetworkConfiguration::getSelectedInterface()
	{
		if(!this->isUserOptionValid())
			return NULL;

		pcap_if_t* currDevice  = NULL;
		int 	   deviceIndex = 1;

		for(currDevice = _devices; currDevice != NULL;
				currDevice = currDevice->next, deviceIndex++)
		{
			if(deviceIndex == _userOption)
				break;
		}

		return currDevice;
	}

	NetworkConfiguration::~NetworkConfiguration() {
		pcap_freealldevs(_devices);
	}
}
