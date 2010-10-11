/*
 * Sniffer.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "Sniffer.h"

Sniffer::Sniffer(pcap_if_t* interface) {

	this->interface = interface;

	printf("Initialising sniffer on : %s\n", interface->name);

	if(pcap_lookupnet(interface->name, &netp, &maskp, errbuf) == -1)
	{
		printf("Error : %s\n", errbuf);
		return;
	}
}

void Sniffer::printInterfaceDetails() {
	char* net;
	char* mask;

	addr.s_addr = netp;
	net = inet_ntoa(addr);
	printf("Network address is %s\n", net);

	addr.s_addr = maskp;
	mask = inet_ntoa(addr);
	printf("Mask address is %s\n", net);

}

void sniffCallback(u_char* arg, const struct pcap_pkthdr* pcktHeader, const u_char* data) {

		struct ether_header* etherHeader = (struct ether_header*)data;

		printf("Grabbed packet of length %d \n", pcktHeader->len);
		printf("Received at %s\n", ctime((const time_t*) &pcktHeader->ts.tv_sec));

		if(ntohs(etherHeader->ether_type) != ETHERTYPE_IP)
		{
			return;
		}
		uint16_t ethtype = ntohs(etherHeader->ether_type);
		printf("Ethernet type is hex : %x, dec : %d \n",
				ethtype, ethtype);

		u_char* details;

		details = etherHeader->ether_shost;

		printf("Source : %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x\n", details[0],details[1],details[2],details[3],
				details[4], details[5]);

		details = etherHeader->ether_dhost;
		printf("Destination : %0.2x:%0.2x:%0.2x:%0.2x:%0.2x:%0.2x\n", details[0],details[1],details[2],details[3],
						details[4], details[5]);
}

void Sniffer::startSniffing() {
	pcap_t* packDescr;
	u_char error[PCAP_ERRBUF_SIZE];
	packDescr = pcap_open_live(interface->name, BUFSIZ, 0, -1, errbuf);
	if(packDescr == NULL) {
		printf("Error : %s", errbuf);
		return;
	}

	pcap_loop(packDescr, -1, sniffCallback, error);
}

Sniffer::~Sniffer() {
	// TODO Auto-generated destructor stub
}
