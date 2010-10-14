/*
 * Reader.h
 *
 *  Created on: 14-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef READER_H_
#define READER_H_

#include <iostream>
#include <string.h>
#include <pcap.h>
#include "common.h"

using namespace std;

namespace network
{
	class Reader
	{
	private:
		const char* _filename;
		const pcap_t* _handler;
		char _errBuf[PCAP_ERRBUF_SIZE];
		int _errCode;
		int openCaptureFile();

	public:
		Reader(const char*);
		void printDetails();
		virtual ~Reader();
	};
}
#endif /* READER_H_ */
