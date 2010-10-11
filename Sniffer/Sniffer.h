/*
 * Sniffer.h
 *
 *  Created on: 11-Oct-2010
 *      Author: root
 */

#ifndef SNIFFER_H_
#define SNIFFER_H_
#include <pcap.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <time.h>

class Sniffer {
private:
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t* interface;
	struct in_addr addr;
	bpf_u_int32 netp;
	bpf_u_int32 maskp;

public:
	Sniffer(pcap_if_t*);
	void printInterfaceDetails();
	void startSniffing();
	virtual ~Sniffer();
};

#endif /* SNIFFER_H_ */
