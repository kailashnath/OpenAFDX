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
#include <string>
#include <algorithm>
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;
using std::hex;

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

	public:
		// this variable holds the pcap
		// packet descriptor
		static const pcap_t* packetDescr;
		static vector<const u_char*> packetDataVector;
		Sniffer(pcap_if_t*);
		static void printInterfaceDetails(void);
		static void startSniffing(void);
		static void stopSniffing(void);
		static void monitorSniffer(void);
		virtual ~Sniffer(void);
	};
}
#endif /* SNIFFER_H_ */
