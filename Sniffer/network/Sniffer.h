/*
 * Sniffer.h
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef SNIFFER_H_
#define SNIFFER_H_

#include <arpa/inet.h>
#include "common.h"

namespace network
{
	class Sniffer
	{

	public:
		static int _errorCode;
		explicit Sniffer(pcap_if_t*);
		int static print_iface_details(void);
		int static start_sniffing(void);
		int static stop_sniffing(void);
		static void monitor_sniffer(void);
		virtual ~Sniffer(void);

	private:
		static char _errbuf[PCAP_errbuf_SIZE];
		static pcap_if_t* _interface;
		static struct in_addr _addr;
		static bpf_u_int32 _netp;
		static bpf_u_int32 _maskp;

		// this variable holds the pcap
		// packet descriptor
		static const pcap_t* _packetDescr;

	};
}
#endif /* SNIFFER_H_ */
