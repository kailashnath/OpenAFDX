/*
 * Sequencenumbers.cpp
 *
 *  Created on: 25-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../headers/config/SequenceNumbers.h"

namespace config
{
	unsigned int SequenceHandler::te_sn = 0;
	std::map<unsigned int, unsigned int> SequenceHandler::vl_sn_map;

	unsigned int SequenceHandler::get_te_sn()
	{
		if(te_sn == 65536)
			te_sn = 0;
		++te_sn;
		return (te_sn - 1);
	}

	unsigned int SequenceHandler::get_vl_sn(unsigned int vl_id)
	{
		unsigned int sn = SequenceHandler::vl_sn_map[vl_id];
		if(sn == 255)
			sn = 0;
		SequenceHandler::vl_sn_map[vl_id] = sn + 1;
		return sn + 1;
	}
}
