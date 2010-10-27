/*
 * MessageListener.h
 *
 *  Created on: 26-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef MESSAGELISTENER_H_
#define MESSAGELISTENER_H_

#include "Listener.h"
#include <sstream>
namespace network
{
	namespace listeners
	{
		class MessageListener : public Listener
		{
		public:
			MessageListener();
			bool handle(u_char*, unsigned short);
		};
	}
}


#endif /* MESSAGELISTENER_H_ */
