/*
 * Sniffer.h
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef SNIFFER_H_
#define SNIFFER_H_

#include <vector>
#include <pcap.h>
#include <time.h>
#include <arpa/inet.h>
#include <iostream>
#include "common.h"

using namespace std;

namespace network
{
	class Sniffer
	{
	private:
		static char _errbuf[PCAP_ERRBUF_SIZE];
		static pcap_if_t* _interface;
		static struct in_addr _addr;
		static bpf_u_int32 _netp;
		static bpf_u_int32 _maskp;

		// this variable holds the pcap
		// packet descriptor
		static const pcap_t* _packetDescr;

	public:
		static int _errorCode;
		static vector<const u_char*> _packetDataVector;

		Sniffer(pcap_if_t*);
		int static printInterfaceDetails(void);
		int static startSniffing(void);
		int static stopSniffing(void);
		static void monitorSniffer(void);
		static const pcap_t* getPcapHandler(void);
		virtual ~Sniffer(void);
	};
}
#endif /* SNIFFER_H_ */
