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

			if(-1 == pcap_findalldevs(&_devices, errbuf))
				std::cout << "Failed getting all devices";
	}

	void NetworkConfiguration::show_user_options()
	{
		int choice;
		int index = 1;
		pcap_if_t* currDevice;

		std::cout << "Select one of the below interfaces" << std::endl;

		for(currDevice = _devices; NULL != currDevice;
			currDevice = currDevice->next, index++)
		{
			std::cout << index << "." << currDevice->name << std::endl;
			_noOfInterfaces ++;
		}

		std::cout << "Enter your choice : ";

		// convert the user entered input to integer
		std::cin >> std::dec >> choice;

		this->set_user_option(choice);
	}

	void NetworkConfiguration::set_user_option(int option) {

		if(0 == option || option > _noOfInterfaces)
		{
			std::cout << "Invalid Option" << std::endl;
			return;
		}

		_userOption = option;
	}

	bool NetworkConfiguration::is_option_valid()
	{
		if(0 == _userOption|| _userOption > _noOfInterfaces)
		{
			return false;
		}

		return true;
	}

	pcap_if_t* NetworkConfiguration::get_selected_iface()
	{
		if(!this->is_option_valid())
			return NULL;

		pcap_if_t* currDevice  = NULL;
		int 	   deviceIndex = 1;

		for(currDevice = _devices; NULL != currDevice;
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
