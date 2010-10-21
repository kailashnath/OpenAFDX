/*
 * ICDParser.cpp
 *
 *  Created on: 20-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "ICDParser.h"

namespace parser
{
	ICDParser::ICDParser(const char* filename) : _inputICD(filename) {
		//int counter = 0;
	}

	void ICDParser::load_objects_from_icd()
	{
		std::string line;

		while(!_inputICD.eof())
		{
			getline(_inputICD, line, '\n');


			if(line.rfind("AFDX_OUTPUT_VL", 1) != std::string::npos)
			{
				std::cout << line << " Size is : " << line.size() << std::endl;
				_lines.push_back(line);
			}
			else if(line.rfind("AFDX_INPUT_VL", 1) != std::string::npos)
			{
				// TODO load input vl objects
			}
		}
	}

	bool ICDParser::is_icd_valid()
	{
		return !_inputICD.fail();
	}

	ICDParser::~ICDParser() {
		// TODO Auto-generated destructor stub
	}
}
