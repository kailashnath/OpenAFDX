/*
 * RSET.cpp
 *
 *  Created on: 25-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../headers/commands/RSET.h"

namespace commands
{
	const char* RSET::_command = "RSET";

	RSET::RSET()
	{

	}

	void RSET::build()
	{
		std::cout << RSET::_command << std::endl;
	}

	void RSET::build_command_str(commands::command_string& cmd)
	{
		unsigned char command[2];
		command[0] = 0x00;
		command[1] = 'k';
		cmd.data = new unsigned char[2];
		std::cout << sizeof(cmd.data) << std::endl;
		cmd.length = 2;
		bcopy(command, cmd.data, 2);
	}

	RSET::~RSET()
	{

	}

}
