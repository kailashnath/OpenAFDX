/*
 * common.h
 *
 *  Created on: 22-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <string.h>
#include <string>
#include "stdio.h"

#define SRC_MAC "02:00:00:00:00:40"
#define DST_MAC "03:00:00:00:00:40"
#define DST_MAC_PREFIX "03:00:00:00"
#define TE_IP "10.1.33.0"
#define ES_IP "10.2.33.0"
#define UDP_SRC 50025
#define UDP_DST 50025

namespace network
{
	namespace protocol
	{
		unsigned short csum(unsigned short*, int);
		//unsigned char* itoh(char* number);
		const char* vltomac(unsigned short);
	}
}

#endif /* COMMON_H_ */
