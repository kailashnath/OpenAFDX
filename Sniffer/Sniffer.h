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

using namespace std;

class Sniffer {
private:
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t* interface;
	struct in_addr addr;
	bpf_u_int32 netp;
	bpf_u_int32 maskp;
	void test();

public:
	// this variable holds the pcap
	// packet descriptor
	static const pcap_t* packetDescr;
	static vector<const u_char*> packetDataVector;
	Sniffer(pcap_if_t*);
	void printInterfaceDetails(void);
	void startSniffing(void);
	void stopSniffing(void);
	virtual ~Sniffer(void);
};

#endif /* SNIFFER_H_ */
