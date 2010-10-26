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
#include <string.h>
#include <stddef.h>

namespace network
{
	class Listener
	{
	public:
		virtual bool handle(u_char* message) const = 0;
	};
}

#endif /* LISTENER_H_ */
