/*
 * Sniffer.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "Sniffer.h"



// initialize the descriptor initially to NULL
const pcap_t* Sniffer::packetDescr = NULL;
vector<const u_char*> packetDataVector;

Sniffer::Sniffer(pcap_if_t* interface) {

	if(Sniffer::packetDescr != NULL)
	{
		printf("Sniffer already running !");
		return;
	}

	this->interface = interface;
	printf("Initializing sniffer on : %s\n", interface->name);

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

		packetDataVector.push_back(data);

		if(packetDataVector.size() == 1000)
		{
			Sniffer snf(NULL);
			snf.stopSniffing();
			return;
		}
		struct pcap_pkthdr* packetHeader = (struct pcap_pkthdr*) pcktHeader;
		struct ether_header* etherHeader = (struct ether_header*)data;
		printf("Grabbed packet of length %d \n", packetHeader->len);
		printf("Received at %s\n", ctime((const time_t*) &packetHeader->ts.tv_sec));

		if(ntohs(etherHeader->ether_type) != ETHERTYPE_IP)
		{
			return;
		}
		uint16_t ethtype = ntohs(etherHeader->ether_type);
		printf("Ethernet type is hex : %x, dec : %d \n",
				ethtype, ethtype);

		u_char* details;

		details = etherHeader->ether_shost;

		printf("Source : %02x:%02x:%02x:%02x:%02x:%02x\n",
				details[0], details[1],
				details[2], details[3],
				details[4], details[5]);

		details = etherHeader->ether_dhost;
		printf("Destination : %02x:%02x:%02x:%02x:%02x:%02x\n",
				details[0], details[1],
				details[2], details[3],
				details[4], details[5]);
}

void Sniffer::startSniffing() {

	u_char error[PCAP_ERRBUF_SIZE];
	packetDescr = pcap_open_live(interface->name, BUFSIZ, 0, -1, errbuf);
	if(packetDescr == NULL) {
		printf("Error : %s", errbuf);
		return;
	}

	pcap_loop((pcap_t*)packetDescr, -1, sniffCallback, error);
}

void Sniffer::stopSniffing() {
	pcap_breakloop((pcap_t*)packetDescr);
}

Sniffer::~Sniffer() {
	// TODO Auto-generated destructor stub
}
