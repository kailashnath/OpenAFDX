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

	void RSET::build_command(commands::command_string& cmdstr)
	{
		int size = sizeof(struct command);
		unsigned char buffer[size];

		struct command* cmd = (struct command*) buffer;
		cmd->sn = htons(config::SequenceHandler::get_te_sn());

		bcopy(RSET::_command, cmd->cmd, sizeof(cmd->cmd));
		cmdstr.data = new unsigned char[size];

		bcopy(cmd, cmdstr.data, size);
		cmdstr.length = size;

	}

	RSET::~RSET()
	{

	}

}
