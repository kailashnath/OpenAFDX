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
