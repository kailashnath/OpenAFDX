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
	const static short TYPE_OUTPUT = 1;
	const static short TYPE_INPUT  = 2;

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

			char* _phys_port_id;
			char* _pin_name;
			char* _line_emc_protection;
			char _network_id;
			char* _connector_name;
			char* _vl_name;
			char* _network_select;
			char* _port_master_name;
			char* _src_ip;
			char* _dst_ip;

			bool _ip_frag_allowed;

		private:
			void init(void);
	};
}
#endif /* OUTPUTVL_H_ */
