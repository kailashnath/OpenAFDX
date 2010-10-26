/*
 * MessageListener.cpp
 *
 *  Created on: 26-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */
#include "../headers/network/MessageListener.h"

namespace network
{

	MessageListener::MessageListener()
	{

	}

	bool MessageListener::handle(u_char* payload)
	{
		std::string message((char*) payload);
		if(message.find("OK", 0) != std::string::npos)
		{
			return true;
		}
		return false;
	}
}
