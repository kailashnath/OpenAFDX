/*
 * OutputVL.cpp
 *
 *  Created on: 23-Oct-2010
 *      Author: root
 */

#include "VirtualLink.h"

namespace config
{
	VirtualLink::VirtualLink()
	{
		// TODO Auto-generated constructor stub
		init();
	}

	VirtualLink::VirtualLink(std::vector<std::string>& values)
	{
		init();
		std::cout << "Size of values is : " << values.size() << std::endl;
		std::cout << values[24] << std::endl;
	}

	void VirtualLink::init(void)
	{
		_type = DEFAULT;
		_phys_port_speed = DEFAULT;
		_bag = DEFAULT;
		_mfs = DEFAULT;
		_no_of_subvls = DEFAULT;
		_sub_vl_id = DEFAULT ;
		_port_id = DEFAULT;
		_vl_id = DEFAULT;
		_port_characteristic = DEFAULT;
		 _port_transmission_type = DEFAULT;
		_src_udp = DEFAULT;
		_dst_udp = DEFAULT;
		_ip_frag_allowed = false;
	}
	VirtualLink::~VirtualLink()
	{
		// TODO Auto-generated destructor stub
	}
}
