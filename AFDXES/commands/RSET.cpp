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

	commands::command_string RSET::get_command_str()
	{
		unsigned char command[2];
		command_string cmd;
		command[0] = 0x00;
		command[1] = 'k';
		cmd.values = command;
		return cmd;
	}

	RSET::~RSET()
	{

	}

}
