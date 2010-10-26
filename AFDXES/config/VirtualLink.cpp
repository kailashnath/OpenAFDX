/*
 * OutputVL.cpp
 *
 *  Created on: 23-Oct-2010
 *      Author: root
 */

#include "../headers/config/VirtualLink.h"

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
		if(values.size() < 25)
			return;
		_phys_port_id 	 	 = values[1];
		_phys_port_speed 	 = atoi(values[2].c_str());
		_pin_name 		 	 = values[3];
		_line_emc_protection = values[4];
		_network_id 		 = values[5].c_str()[0];
		_connector_name 	 = values[6];
		_vl_id 			  	 = atoi(values[7].c_str());
		_vl_name 			 = values[8];
		_network_select		 = values[9];
		_bag 				 = atoi(values[10].c_str());
		_mfs 				 = atoi(values[11].c_str());
		_no_of_subvls 		 = atoi(values[12].c_str());
		_sub_vl_id 			 = atoi(values[13].c_str());
		_port_id 			 = atoi(values[14].c_str());
		_port_master_name 	 = values[15];

		// We are reject values[16] as it defines AFDX port type in
		// icd which is always AFDX communcation port

		if(values[17].find("Sampling", 0) != std::string::npos)
		{
			_port_characteristic = PORT_SAMPLING;
		}
		else if (values[17].find("Queuing", 0) != std::string::npos)
		{
			_port_characteristic = PORT_QUEUING;
		}
		else if (values[17].find("SAP", 0) != std::string::npos)
		{
			_port_characteristic = PORT_SAP;
		}

		if(values[18].find("yes", 0) != std::string::npos)
			_ip_frag_allowed = true;
		else
			_ip_frag_allowed = false;

		if(values[19].find("unicast", 0) != std::string::npos)
			_port_characteristic = TRANSMISSION_UNICAST;
		else
			_port_characteristic = TRANSMISSION_MULTICAST;

		_src_ip    = const_cast<char*>(values[20].c_str());
		_dst_ip    = const_cast<char*>(values[21].c_str());
		_src_udp   = atoi(values[22].c_str());
		_dst_udp   = atoi(values[23].c_str());
		_buff_size = atoi(values[24].c_str());
		_dst_mac   = DST_MAC_PREFIX;
		_dst_mac.append(network::protocol::vltomac(_vl_id));
	}

	void VirtualLink::init(void)
	{
		_type 					= DEFAULT;
		_phys_port_speed 		= DEFAULT;
		_bag 					= DEFAULT;
		_mfs 					= DEFAULT;
		_no_of_subvls 			= DEFAULT;
		_sub_vl_id				= DEFAULT;
		_port_id 				= DEFAULT;
		_vl_id 					= DEFAULT;
		_port_characteristic    = DEFAULT;
		_port_transmission_type = DEFAULT;
		_src_udp 				= DEFAULT;
		_dst_udp 				= DEFAULT;
		_ip_frag_allowed 		= false;
		_network_id 			= DEFAULT_NETWORK;
		_type_command 			= false;
	}

	config::VirtualLink* VirtualLink::get_default_vl()
	{
		config::VirtualLink* vl = new config::VirtualLink();
		vl->_buff_size = 8192;

		return vl;
	}

	VirtualLink::~VirtualLink()
	{
		// TODO Auto-generated destructor stub
	}
}
