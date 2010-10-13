/*
 * Sniffer.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "Sniffer.h"

namespace network
{
	const pcap_t* Sniffer::packetDescr = NULL;
	pcap_if_t* Sniffer::interface 	   = NULL;
	bpf_u_int32 Sniffer::netp 		   = NULL;
	bpf_u_int32 Sniffer::maskp 		   = NULL;

	// allocate space for static variables
	struct in_addr Sniffer::addr;
	char Sniffer::errbuf[PCAP_ERRBUF_SIZE];
	vector<const u_char*> Sniffer::packetDataVector;

	Sniffer::Sniffer(pcap_if_t* interface)
	{

		if(Sniffer::packetDescr != NULL)
		{
			cout << "Sniffer already running !";
			return;
		}

		Sniffer::interface = interface;
		cout << "Initializing sniffer on : " << Sniffer::interface->name << endl;

		if(pcap_lookupnet(Sniffer::interface->name, &netp, &maskp, errbuf) == -1)
		{
			cout << "Error : " << errbuf << endl;
			return;
		}
	}

	void Sniffer::printInterfaceDetails()
	{
		char* net;
		char* mask;

		Sniffer::addr.s_addr = netp;

		net = inet_ntoa(addr);
		cout << "Network address is " << net << endl;

		Sniffer::addr.s_addr = maskp;
		mask = inet_ntoa(Sniffer::addr);
		cout << "Mask address is " << net << endl;

	}

	void sniffCallback(u_char* arg, const struct pcap_pkthdr* pcktHeader,
					  const u_char* data) {

			Sniffer::packetDataVector.push_back(data);

			struct pcap_pkthdr* packetHeader = (struct pcap_pkthdr*) pcktHeader;
			struct ether_header* etherHeader = (struct ether_header*)data;
			cout << "Grabbed packet of length " << packetHeader->len << endl;
			cout << "Received at " << ctime((const time_t*) &packetHeader->ts.tv_sec) << endl;

			if(ntohs(etherHeader->ether_type) != ETHERTYPE_IP)
			{
				return;
			}
			uint16_t ethtype = ntohs(etherHeader->ether_type);
			cout << "Ethernet type is hex : " << hex << ethtype << ", dec : "
					<< dec << (int)ethtype << endl;

			u_char* details;

			details = etherHeader->ether_shost;

			cout << "Source : "
					<< hex << setfill('0') << setw(2) << (int) details[0] << ":"
					<< setw(2) << (int) details[1] << ":"
					<< setw(2) << (int) details[2] << ":"
					<< setw(2) << (int) details[3] << ":"
					<< setw(2) << (int) details[4] << ":"
					<< setw(2) << (int) details[5] << endl;

			details = etherHeader->ether_dhost;
			cout << "Destination : "
							<< hex << setfill('0') << setw(2) << (int) details[0] << ":"
							<< setw(2) << (int) details[1] << ":"
							<< setw(2) << (int) details[2] << ":"
							<< setw(2) << (int) details[3] << ":"
							<< setw(2) << (int) details[4] << ":"
							<< setw(2) << (int) details[5] << endl;

	}

	void Sniffer::startSniffing() {

		static u_char* error;
		packetDescr = pcap_open_live(interface->name, BUFSIZ, 0, -1, errbuf);

		if(packetDescr == NULL) {
			cout << "Error : " << errbuf << endl;
			return;
		}

		pcap_loop((pcap_t*)packetDescr, -1, sniffCallback, error);
	}

	void Sniffer::monitorSniffer(void)
	{
		while(Sniffer::packetDataVector.size() < 100)
		{
			cout << "Size of vector is " << Sniffer::packetDataVector.size() << endl;
			sleep(1);
		}
		Sniffer::stopSniffing();
	}

	void Sniffer::stopSniffing() {
		cout << "Stopping sniffer";
		pcap_breakloop((pcap_t*)packetDescr);
	}


	Sniffer::~Sniffer() {
		// TODO Auto-generated destructor stub
	}
}
