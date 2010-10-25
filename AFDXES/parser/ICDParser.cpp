/*
 * ICDParser.cpp
 *
 *  Created on: 20-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../headers/parser/ICDParser.h"

namespace parser
{
	ICDParser::ICDParser(const char* filename) : _inputICD(filename),
			_output_vl(NULL), _input_vl(NULL)
	{
		//int counter = 0;
	}

	void ICDParser::load_objects_from_icd()
	{
		std::string line;
		if(!_inputICD.good())
			return;
		while(!_inputICD.eof())
		{
			getline(_inputICD, line, '\n');

			if(line.rfind("AFDX_OUTPUT_VL", 0) != std::string::npos)
			{

				std::vector<std::string> values;

				boost::split(values, line, boost::is_any_of(";"));
				config::VirtualLink link(values);
				link._type = config::TYPE_OUTPUT;

			}
			else if(line.rfind("AFDX_INPUT_VL", 0) != std::string::npos)
			{
				std::vector<std::string> values;
				boost::split(values, line, boost::is_any_of(";"));
				config::VirtualLink link(values);
				link._type = config::TYPE_INPUT;
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
