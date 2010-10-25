/*
 * ICDParser.h
 *
 *  Created on: 20-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef ICDPARSER_H_
#define ICDPARSER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "../config/VirtualLink.h"

namespace parser
{
	class ICDParser {
	public:
		ICDParser(const char* filename);
		bool is_icd_valid(void);
		void load_objects_from_icd(void);
		void get_objects(short type);
		virtual ~ICDParser();

	private:
		std::ifstream _inputICD;
		std::vector<config::VirtualLink> _output_vl;
		std::vector<config::VirtualLink> _input_vl;

	};
}
#endif /* ICDPARSER_H_ */
