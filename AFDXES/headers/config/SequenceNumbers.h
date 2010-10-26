/*
 * SequenceNumber.h
 *
 *  Created on: 25-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef SEQUENCENUMBER_H_
#define SEQUENCENUMBER_H_

#include <iostream>
#include <map>
#include <stdlib.h>

namespace config
{
	class SequenceHandler
	{
	public:
		static unsigned int get_te_sn();
		static unsigned int get_vl_sn(unsigned int);

	private:
		static unsigned int te_sn;
		static std::map<unsigned int, unsigned int> vl_sn_map;

	};
}

#endif /* SEQUENCENUMBER_H_ */
