/*
 * Reader.cpp
 *
 *  Created on: 14-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../headers/network/Reader.h"

namespace network
{
	Reader::Reader(const char* filename) : _handler(NULL), _errCode(0)
	{
		this->_filename = filename;
		this->open_capture_file();
	}

	void Reader::print_details(void)
	{
		u_char* error = NULL;
		if(pcap_loop(const_cast<pcap_t*>(this->_handler), 0,
				common::pcapCallback, error) == -1)
		{
			std::cout << "Error while reading the capture file : " << error
					<< std::endl;
		}
	}

	int Reader::open_capture_file()
	{
		this->_handler = pcap_open_offline(this->_filename, this->_errbuf);
		if(this->_handler == NULL)
		{
			std::cout << "Failed opening the capture file " << std::endl;
			this->_errCode = -1;
			return -1;
		}

		struct bpf_program program;
		pcap_compile(const_cast<pcap_t*>(_handler), &program,
								common::kafdxFilterExperssion.c_str(), 1, NULL);

		if(pcap_setfilter(const_cast<pcap_t*>(_handler), &program) == -1)
		{
			std::cout << "Error assigning filter " << std::endl;
			_errCode = -1;
			return -1;
		}

		return 0;
	}

	Reader::~Reader()
	{
		// TODO Auto-generated destructor stub
	}
}
