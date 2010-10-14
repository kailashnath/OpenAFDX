/*
 * Reader.cpp
 *
 *  Created on: 14-Oct-2010
 *      Author: root
 */

#include "Reader.h"

Reader::Reader(const char* filename) : _handler(NULL), _errCode(0) {
	this->_filename = filename;
	this->openCaptureFile();
}

int Reader::openCaptureFile()
{
	this->_handler = pcap_open_offline(this->_filename, this->_errBuf);
	if(this->_handler == NULL)
	{
		cout << "Failed opening the capture file " << endl;
	}
	struct bpf_program program;
	pcap_compile(const_cast<pcap_t*>(_handler), &program,
							"ip and udp", 1, NULL);

	if(pcap_setfilter(const_cast<pcap_t*>(_handler), &program) == -1)
	{
		cout << "Error assigning filter " << endl;
		_errCode = -1;
		return -1;
	}

	return 0;
}

void Reader::printDetails(void)
{
	u_char* error = NULL;
	if(-1 == pcap_loop(const_cast<pcap_t*>(this->_handler), 0, pcapCallback, error))
	{
		cout << "Error while reading the capture file : " << error << endl;
	}
}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}
