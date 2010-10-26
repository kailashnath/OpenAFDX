/*
 * common.h
 *
 *  Created on: 14-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <ctime>
#include <vector>
#include <string.h>
#include <pcap.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include "Sniffer.h"

namespace network
{
	class common
	{
	public :
		static const std::string kafdxFilterExperssion;
		static std::vector<const u_char*> packetDataVector;
		static void (*responseListener)(char*);
		static void pcapCallback(u_char*, const struct pcap_pkthdr*, const u_char*);
		static void show_packet_details(const struct pcap_pkthdr*);
		static void show_ether_details(const struct ether_header*);
		static void show_ip_details(const struct iphdr*);
		static void show_udp_details(const struct udphdr*);
		static void show_payload(const u_char*);
	};
	unsigned short csum(unsigned short*, int);
}
#endif /* COMMON_H_ */
