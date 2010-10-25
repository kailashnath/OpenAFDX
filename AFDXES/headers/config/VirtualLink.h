/*
 * OutputVL.h
 *
 *  Created on: 23-Oct-2010
 *      Author: root
 */

#ifndef OUTPUTVL_H_
#define OUTPUTVL_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "stdlib.h"

#include "common.h"

namespace config
{
	const static unsigned short TYPE_OUTPUT = 1;
	const static unsigned short TYPE_INPUT  = 2;

	class VirtualLink
	{
		public:
			VirtualLink(std::vector<std::string>& values);
			VirtualLink();

			virtual ~VirtualLink();

			unsigned short _type;
			unsigned short _phys_port_speed;
			unsigned short _bag;
			unsigned short _mfs;
			unsigned short _no_of_subvls;
			unsigned short _sub_vl_id;
			unsigned short _port_id;
			unsigned short _vl_id;
			unsigned short _port_characteristic;
			unsigned short _port_transmission_type;
			unsigned short _src_udp;
			unsigned short _dst_udp;
			unsigned short _buff_size;

			std::string _phys_port_id;
			std::string _pin_name;
			std::string _line_emc_protection;
			char _network_id;
			std::string _connector_name;
			std::string _vl_name;
			std::string _network_select;
			std::string _port_master_name;
			std::string _src_ip;
			std::string _dst_ip;

			bool _ip_frag_allowed;

		private:
			void init(void);
	};
}
#endif /* OUTPUTVL_H_ */
