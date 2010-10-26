/*
 * Receiver.cpp
 *
 *  Created on: 26-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../headers/network/Receiver.h"

namespace network
{
	const std::string network::Receiver::kafdxFilterExpression = "ip and udp and udp[6:2] = 0x0";
	pcap_t* network::Receiver::_pd = NULL;

	Receiver::Receiver(std::string interface)
	{
		_interface = interface;
		init();
	}

	void Receiver::init()
	{

		if(_pd != NULL)
		{
			std::cout << "Desc initialized" << std::endl;
			return;
		}

		struct bpf_program program;

		if(pcap_lookupnet(_interface.c_str(),
						&_netp, &_maskp, _error) == -1)
		{
			std::cout << "Error" << std::endl;
		}

		_pd = pcap_open_live(_interface.c_str(), BUFSIZ, 0, -1, _error);

		if(_pd == NULL)
		{
			std::cout << "Failed opening the interface : " << _interface
					<< ". Receiver failed initializing" << std::endl;
			return;
		}

		// AFDX specific filter:
		// filter description : The packet must be of type IP with
		// udp on top of it whose checksum udp[6:2] is '0x0' (6 = position,
		// 2 = offset)
		// udp checksum filter : and udp[6:2] = 0x0
		// omitted temporarily for testing purposes
		pcap_compile(_pd, &program,
				network::Receiver::kafdxFilterExpression.c_str(), 1, _netp);

		if( pcap_setfilter(_pd, &program) == -1)
		{
			std::cout << "Failed setting afdx filter" << std::endl;
			return;
		}
		std::cout << "Initialized successfull" << std::endl;
	}

	void Receiver::register_listener(network::Listener* listener)
	{
		this->_listener = listener;
	}

	void Receiver::listen()
	{
		u_char* datagram;
		unsigned short header_size = sizeof(struct ether_header) +
				sizeof(struct iphdr) + sizeof(struct udphdr);

		if(_listener == NULL)
			return;

		while(true)
		{
			datagram = const_cast<u_char*>(pcap_next(_pd, _phdr));
			if(datagram == NULL)
				continue;
			u_char* payload = datagram + header_size;
			std::cout << "Payload is " << payload << std::endl;

			if((*_listener).handle(payload))
			{
				break;
			}
		}
	}

	void callback(u_char* arg, const struct pcap_pkthdr* pcktHeader,
					  const u_char* data)
	{

	}

	Receiver::~Receiver()
	{
		// TODO Auto-generated destructor stub
	}
}
