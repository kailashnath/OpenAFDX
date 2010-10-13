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
	// allocate space for static variables
	const pcap_t* Sniffer::packetDescr = NULL;
	pcap_if_t* 	  Sniffer::interface   = NULL;
	bpf_u_int32   Sniffer::netp 	   = NULL;
	bpf_u_int32   Sniffer::maskp 	   = NULL;
	int           Sniffer::errorCode   = 0;

	struct in_addr 		  Sniffer::addr;
	char 		   		  Sniffer::errbuf[PCAP_ERRBUF_SIZE];
	vector<const u_char*> Sniffer::packetDataVector;

	Sniffer::Sniffer(pcap_if_t* interface)
	{

		if(packetDescr != NULL)
		{
			cout << "Sniffer already running !" << endl;
			return;
		}
		else if (interface == NULL)
		{
			cout << "Interface cannot be null" << endl;
			errorCode = -1;
			return;
		}

		Sniffer::interface = interface;
		cout << "Initializing sniffer on : " << Sniffer::interface->name << endl;

		if(pcap_lookupnet(Sniffer::interface->name, &netp, &maskp, errbuf) == -1)
		{
			cout << "Error : " << errbuf << endl;
			errorCode = -1;
		}
	}

	int Sniffer::printInterfaceDetails()
	{
		char* net;
		char* mask;

		if(netp == (bpf_u_int32)NULL ||
           maskp == (bpf_u_int32)NULL)
		{
			cout << "Sniffer was not initialized properly" << endl;
			errorCode = -1;
			return -1;
		}

		addr.s_addr = netp;

		net = inet_ntoa(addr);
		cout << "Network address is " << net << endl;

		addr.s_addr = maskp;
		mask = inet_ntoa(addr);
		cout << "Mask address is " << net << endl;

		return 0;
	}

	void sniffCallback(u_char* arg, const struct pcap_pkthdr* pcktHeader,
					  const u_char* data) {

			Sniffer::packetDataVector.push_back(data);

			struct pcap_pkthdr* packetHeader = (struct pcap_pkthdr*) pcktHeader;
			struct ether_header* etherHeader = (struct ether_header*)data;
			cout << "Grabbed packet of length " << dec << (int)packetHeader->len << endl;
			cout << "Received at " << ctime((const time_t*) &packetHeader->ts.tv_sec) << endl;

			if(ntohs(etherHeader->ether_type) != ETHERTYPE_IP)
			{
				cout << "Packet is not of type IP. Discarding packet" << endl;
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

	int Sniffer::startSniffing() {

		static u_char* error;
		struct bpf_program program;

		if(interface == NULL)
		{
			cout << "Undefined interface";
			Sniffer::errorCode = -1;
			return -1;
		}

		packetDescr = pcap_open_live(interface->name, BUFSIZ,
					                 0, -1, errbuf);
		if(packetDescr == NULL) {
			cout << "Failed opening on interface. Error : " << errbuf << endl;
			return -1;
		}

		// AFDX specific filter:
		// filter description : The packet must be of type IP with
		// udp on top of it whose checksum udp[6:2] is '0x0' (6 = position,
		// 2 = offset)
		pcap_compile((pcap_t*)packetDescr, &program,
					"ip and udp and (udp[6:2] = 0x0)", 1,
					 Sniffer::netp);

		if (pcap_setfilter((pcap_t*) packetDescr, &program) == -1)
		{
			cout << "Failed setting the AFDX filter" << endl;
			errorCode = -1;
			stopSniffing();
			return -1;
		}

		pcap_loop((pcap_t*)packetDescr, -1, sniffCallback, error);
		return 0;
	}

	// code written temporarily for testing purposes.
	void Sniffer::monitorSniffer(void)
	{
		while(packetDataVector.size() < 100 && errorCode > -1)
		{
			cout << "Size of vector is " << dec << (int)packetDataVector.size() << endl;
			sleep(1);
		}

		Sniffer::stopSniffing();
	}

	int Sniffer::stopSniffing() {
		cout << "Stopping sniffer";
		pcap_breakloop((pcap_t*)packetDescr);
		return 0;
	}

	Sniffer::~Sniffer() {
		// TODO Auto-generated destructor stub
	}
}
