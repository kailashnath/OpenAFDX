/*
 * NetworkConfiguration.h
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef NETWORKCONFIGURATION_H_
#define NETWORKCONFIGURATION_H_
#include "pcap.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace network
{
	class NetworkConfiguration {
	private:
		pcap_if_t* _devices;
		int _noOfInterfaces;
		int _userOption;
		void setUserOption(int);

	public:
		NetworkConfiguration();
		void showUserOptions();
		bool isUserOptionValid();
		pcap_if_t* getSelectedInterface();
		virtual ~NetworkConfiguration();

	};
}
#endif /* NETWORKCONFIGURATION_H_ */
