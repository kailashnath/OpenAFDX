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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

namespace network
{
	class Sniffer
	{
	private:
		static char errbuf[PCAP_ERRBUF_SIZE];
		static pcap_if_t* interface;
		static struct in_addr addr;
		static bpf_u_int32 netp;
		static bpf_u_int32 maskp;
		// this variable holds the pcap
		// packet descriptor
		static const pcap_t* packetDescr;

	public:
		static int errorCode;
		static vector<const u_char*> packetDataVector;

	public:
		Sniffer(pcap_if_t*);
		int static printInterfaceDetails(void);
		int static startSniffing(void);
		int static stopSniffing(void);
		static void monitorSniffer(void);
		virtual ~Sniffer(void);
	};
}
#endif /* SNIFFER_H_ */