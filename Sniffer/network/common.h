/*
 * common.h
 *
 *  Created on: 14-Oct-2010
 *      Author: root
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

using namespace std;
static vector<const u_char*> packetDataVector;
void pcapCallback(u_char*, const struct pcap_pkthdr*, const u_char*);
void showPacketDetails(const struct pcap_pkthdr*);
void showEthernetDetails(const struct ether_header*);
void showIPDetails(const struct iphdr*);
void showUDPDetails(const struct udphdr*);
void showPayload(const u_char*);
#endif /* COMMON_H_ */
