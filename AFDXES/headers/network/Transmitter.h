/*
 * Transmitter.h
 *
 *  Created on: 22-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <iostream>
#include <string.h>
#include <pcap.h>

#include "NetworkConfiguration.h"

namespace network
{
	class Transmitter {
	public:
		Transmitter(char*, char*);
		int do_transmit(const u_char* buffer, int size, short network_select,
				int repeat_count, bool break_on_failure);

		char* get_error(void);
		virtual ~Transmitter();
	private:
		const static pcap_t* _pcap_descr_a;
		const static pcap_t* _pcap_descr_b;

		char _error[PCAP_ERRBUF_SIZE];
	};
}
#endif /* TRANSMITTER_H_ */
