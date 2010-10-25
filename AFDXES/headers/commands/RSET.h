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
#include <boost/format.hpp>
#include "../config/SequenceNumbers.h"
#include "CommandString.h"

namespace commands
{
	class RSET
	{
	public:
		RSET();
		void build(void);
		const commands::command_string get_command_str(void);
		virtual ~RSET();
	private:
		const static char* _command;
	};
}

#endif /* RSET_H_ */
