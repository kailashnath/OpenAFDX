/*
 * Listener.h
 *
 *  Created on: 26-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef LISTENER_H_
#define LISTENER_H_

#include <string>
#include <sys/types.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>

namespace network
{
	namespace listeners
	{
		class Listener
		{
		public:
			virtual bool handle(u_char* message, unsigned short) = 0;
		};
	}
}

#endif /* LISTENER_H_ */
