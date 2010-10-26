/*
 * Receiver.h
 *
 *  Created on: 26-Oct-2010
 *      Author: root
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <pcap.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include "Listener.h"

namespace network
{
	class Receiver {
	public:
		const static std::string kafdxFilterExpression;

		Receiver(std::string);
		void register_listener(network::Listener*);
		void listen(void);
		virtual ~Receiver();
	private:
		char _error[PCAP_ERRBUF_SIZE];
		std::string _interface;
		static pcap_t* _pd;
		pcap_pkthdr* _phdr;
		bpf_u_int32 _netp;
		bpf_u_int32 _maskp;
		network::Listener* _listener;
		void init(void);
	};
	void callback(u_char* arg, const struct pcap_pkthdr* pcktHeader,
						  const u_char* data);
}
#endif /* RECEIVER_H_ */
