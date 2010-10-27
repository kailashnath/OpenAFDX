/*
 * MessageListener.cpp
 *
 *  Created on: 26-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */
#include "../../headers/network/listeners/MessageListener.h"

namespace network
{
	namespace listeners
	{
		MessageListener::MessageListener()
		{

		}

		bool MessageListener::handle(u_char* payload, unsigned short size)
		{
			unsigned short header_size = sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
			unsigned short payload_size = size - header_size;

			std::cout << "Total size " << std::dec << size << std::endl;
			std::cout << "Payload length " << payload_size << std::endl;
			std::string message;
			int i = 0;

			while( i <= payload_size)
			{
				std::stringstream ss;
				ss << std::hex << ntohs(payload[i + header_size]);

				++i;
			}
			std::cout << char(65) << std::endl;
			return false;
		}
	}
}
