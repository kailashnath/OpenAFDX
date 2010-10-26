/*
 * common.cpp
 *
 *  Created on: 22-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../../headers/network/protocol/common.h"

namespace network
{
	namespace protocol
	{
		unsigned short csum (unsigned short* buf, int nwords)
		{
		  unsigned long sum;
		  for (sum = 0; nwords > 0; nwords--)
			sum += *buf++;
		  sum = (sum >> 16) + (sum & 0xffff);
		  sum += (sum >> 16);
		  return ~sum;
		}

		const char* vltomac(unsigned short vl_id)
		{
			char vl_mac[4];
			sprintf(vl_mac, "%04x", vl_id);
			std::string mac;
			mac.append(":");
			mac.append(vl_mac, 2);
			mac.append(":");
			mac.append(vl_mac + 2, 2);
			return mac.c_str();
		}
		/*unsigned char* itoh(unsigned int number)
		{
			char* hexvals = "0123456789abcdef";
			int digit = 0;
			unsigned char value[10];

			if(( digit = number / 16) != 0)
			{

			}
			else
			{

			}
			return value;
		}*/
	}
}
