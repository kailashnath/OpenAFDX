/*
 * Global.h
 *
 *  Created on: 26-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

namespace config
{
	struct Network
	{
		const char selected_interface;
		unsigned short int rx_vl_a;
		unsigned short int rx_vl_b;
		unsigned short int tx_udp_port;
		unsigned short int rx_udp_port;
		const char* interface_A;
		const char* interface_B;
		const char* ip_es;
	} Config = {'A', 1, 2, 50025, 50025, "eth0", "eth1", "10.1.33.0"};
}

#endif /* GLOBAL_H_ */
