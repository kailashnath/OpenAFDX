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
		pcap_if_t* devices;
		int setUserOption(int);
		int noOfInterfaces;
		int userOption;

	public:
		NetworkConfiguration();
		void showUserOptions();
		pcap_if_t* getSelectedInterface();
		virtual ~NetworkConfiguration();
	};
}
#endif /* NETWORKCONFIGURATION_H_ */
