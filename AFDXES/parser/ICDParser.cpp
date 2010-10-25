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
		if(!is_icd_valid())
		{
			std::cout << "The given icd file is not valid" << std::endl;
		}
	}

	bool ICDParser::is_icd_valid()
	{
		return _inputICD.good();
	}

	unsigned short ICDParser::load_objects_from_icd()
	{
		std::string line;

		if(!_inputICD.good())
		{
			return -1;
		}

		while(!_inputICD.eof())
		{
			getline(_inputICD, line, '\n');

			if(line.rfind("AFDX_OUTPUT_VL", 0) != std::string::npos)
			{
				std::vector<std::string> values;
				boost::split(values, line, boost::is_any_of(";"));
				config::VirtualLink link(values);
				link._type = config::TYPE_OUTPUT;
				_output_vl.push_back(link);
			}
			else if(line.rfind("AFDX_INPUT_VL", 0) != std::string::npos)
			{
				std::vector<std::string> values;
				boost::split(values, line, boost::is_any_of(";"));
				config::VirtualLink link(values);
				link._type = config::TYPE_INPUT;

				_input_vl.push_back(link);
			}
		}
		cleanup();
		return 0;
	}

	std::vector<config::VirtualLink> ICDParser::get_objects(short type)
	{
		if(type == config::TYPE_OUTPUT)
			return _output_vl;
		else if (type == config::TYPE_INPUT)
			return _input_vl;
		else
		{
			std::vector<config::VirtualLink> empty;
			return empty;
		}
	}

	void ICDParser::cleanup(void)
	{
		_inputICD.close();
	}

	ICDParser::~ICDParser() {
		// TODO Auto-generated destructor stub
	}
}
