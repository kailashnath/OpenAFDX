/*
 * Transmitter.cpp
 *
 *  Created on: 22-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../headers/network/Transmitter.h"

namespace network
{

	const pcap_t* Transmitter::_pcap_descr_a = NULL;
	const pcap_t* Transmitter::_pcap_descr_b = NULL;

	Transmitter::Transmitter(char* interface_a, char* interface_b)
	{
		strcpy(_error, "");

		if(_pcap_descr_a == NULL && interface_a != NULL)
		{
			_pcap_descr_a = pcap_open_live(interface_a, BUFSIZ, 0, -1, _error);
		}

		if(_pcap_descr_b == NULL && interface_b != NULL)
		{
			_pcap_descr_b = pcap_open_live(interface_b, BUFSIZ, 0, -1, _error);
		}
	}

	int Transmitter::do_transmit(const u_char* data, int size,
			short network_select = NetworkConfiguration::NETWORK_A,
			int repeat_count = 1, bool break_on_failure = false)
	{
		int status = 0;
		while(repeat_count > 0)
		{
			if(network_select == NetworkConfiguration::NETWORK_A)
				status = pcap_sendpacket(const_cast<pcap_t*>(_pcap_descr_a),
						data, size);
			else if (network_select == NetworkConfiguration::NETWORK_B)
				status = pcap_sendpacket(const_cast<pcap_t*>(_pcap_descr_b),
						data, size);
			else if (network_select == NetworkConfiguration::NETWORK_AB)
			{
				status = pcap_sendpacket(const_cast<pcap_t*>(_pcap_descr_a),
						data, size) ||
						pcap_sendpacket(const_cast<pcap_t*>(_pcap_descr_b),
								data, size);
			}
			else
			{
				std::cout << "Status is " << status << std::endl;
				strcpy(_error, "Invalid network_select parameter");
				return -1;
			}
			if (break_on_failure && status != 0)
				return -1;

			--repeat_count;
		}
		return status;
	}

	char* Transmitter::get_error(void)
	{
		return _error;
	}

	Transmitter::~Transmitter()
	{
		delete _error;
	}
}
