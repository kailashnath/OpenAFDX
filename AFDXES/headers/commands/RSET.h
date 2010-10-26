/*
 * RSET.h
 *
 *  Created on: 25-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef RSET_H_
#define RSET_H_

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <boost/format.hpp>

#include "CommandString.h"
#include "../config/SequenceNumbers.h"

namespace commands
{
	struct command
	{
		unsigned short int sn;
		unsigned char cmd[4];
	};

	class RSET
	{
	public:
		RSET();
		void build(void);
		void build_command(command_string&);
		virtual ~RSET();
	private:
		const static char* _command;
	};
}

#endif /* RSET_H_ */
