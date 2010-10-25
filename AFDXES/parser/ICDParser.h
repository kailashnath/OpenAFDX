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
#include <string>
#include <boost/tokenizer.hpp>

namespace parser
{
	class ICDParser {
	public:
		ICDParser(const char* filename);
		bool is_icd_valid(void);
		void load_objects_from_icd(void);

		virtual ~ICDParser();

	private:
		std::vector<std::string> _lines;
		std::ifstream _inputICD;

	};
}
#endif /* ICDPARSER_H_ */
