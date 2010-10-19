/*
 * Reader.h
 *
 *  Created on: 14-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef READER_H_
#define READER_H_

#include "common.h"

namespace network
{
	class Reader
	{
	public:
		Reader(const char*);
		void print_details();
		virtual ~Reader();

	private:
		const char* _filename;
		const pcap_t* _handler;
		char _errbuf[PCAP_errbuf_SIZE];
		int _errCode;
		int open_capture_file();
	};
}
#endif /* READER_H_ */
