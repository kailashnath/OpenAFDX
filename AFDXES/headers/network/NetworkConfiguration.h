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

namespace network
{
	class NetworkConfiguration
	{
	public:
		NetworkConfiguration();
		void show_user_options();
		bool is_option_valid();
		pcap_if_t* get_selected_iface();
		virtual ~NetworkConfiguration();

		static const short NETWORK_AB = 0;
		static const short NETWORK_A = 1;
		static const short NETWORK_B = 2;

	private:
		pcap_if_t* _devices;
		int _noOfInterfaces;
		int _userOption;
		void set_user_option(int);

	};
}
#endif /* NETWORKCONFIGURATION_H_ */
