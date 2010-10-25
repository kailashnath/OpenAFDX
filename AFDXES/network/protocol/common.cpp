/*
 * common.cpp
 *
 *  Created on: 22-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../../headers/network/protocol/common.h"

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
	}
