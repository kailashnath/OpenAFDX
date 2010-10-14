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
	const pcap_t* Sniffer::_packetDescr = NULL;
	pcap_if_t* 	  Sniffer::_interface   = NULL;
	bpf_u_int32   Sniffer::_netp 	   = NULL;
	bpf_u_int32   Sniffer::_maskp 	   = NULL;
	int           Sniffer::_errorCode   = 0;

	struct in_addr 		  Sniffer::_addr;
	char 		   		  Sniffer::_errbuf[PCAP_ERRBUF_SIZE];
	vector<const u_char*> Sniffer::_packetDataVector;

	Sniffer::Sniffer(pcap_if_t* interface)
	{

		if(_packetDescr != NULL)
		{
			cout << "Sniffer already running !" << endl;
			return;
		}
		else if (interface == NULL)
		{
			cout << "Interface cannot be null" << endl;
			_errorCode = -1;
			return;
		}

		Sniffer::_interface = interface;
		cout << "Initializing sniffer on : " << Sniffer::_interface->name << endl;

		if(pcap_lookupnet(Sniffer::_interface->name, &_netp, &_maskp, _errbuf) == -1)
		{
			cout << "Error : " << _errbuf << endl;
			_errorCode = -1;
		}
	}

	int Sniffer::printInterfaceDetails()
	{
		char* net;
		char* mask;

		if(_netp == (bpf_u_int32)NULL ||
           _maskp == (bpf_u_int32)NULL)
		{
			cout << "Sniffer was not initialized properly" << endl;
			_errorCode = -1;
			return -1;
		}

		_addr.s_addr = _netp;
		net = inet_ntoa(_addr);
		cout << "Network address is " << net << endl;

		_addr.s_addr = _maskp;
		mask = inet_ntoa(_addr);
		cout << "Mask address is " << net << endl;

		return 0;
	}

	void sniffCallback(u_char* arg, const struct pcap_pkthdr* pcktHeader,
					  const u_char* data) {

			Sniffer::_packetDataVector.push_back(data);

			struct ether_header* etherHeader =
					reinterpret_cast<struct ether_header*>(
							const_cast<u_char*>(data));
			cout << "Grabbed packet of length " << dec << static_cast<int>(pcktHeader->len) << endl;

			cout << "Received at " << ctime(const_cast<const time_t*>(&(pcktHeader->ts.tv_sec))) << endl;

			if(ntohs(etherHeader->ether_type) != ETHERTYPE_IP)
			{
				cout << "Packet is not of type IP. Discarding packet" << endl;
				return;
			}
			uint16_t ethtype = ntohs(etherHeader->ether_type);
			cout << "Ethernet type is hex : " << hex << ethtype << ", dec : "
					<< dec << static_cast<int>(ethtype) << endl;

			u_char* details;

			details = etherHeader->ether_shost;

			cout << "Source : "
					<< hex << setfill('0')
					<< setw(2) << static_cast<int>(details[0]) << ":"
					<< setw(2) << static_cast<int>(details[1]) << ":"
					<< setw(2) << static_cast<int>(details[2]) << ":"
					<< setw(2) << static_cast<int>(details[3]) << ":"
					<< setw(2) << static_cast<int>(details[4]) << ":"
					<< setw(2) << static_cast<int>(details[5]) << endl;

			details = etherHeader->ether_dhost;
			cout << "Destination : "
					<< hex << setfill('0')
					<< setw(2) << static_cast<int>(details[0]) << ":"
					<< setw(2) << static_cast<int>(details[1]) << ":"
					<< setw(2) << static_cast<int>(details[2]) << ":"
					<< setw(2) << static_cast<int>(details[3]) << ":"
					<< setw(2) << static_cast<int>(details[4]) << ":"
					<< setw(2) << static_cast<int>(details[5]) << endl;
	}

	int Sniffer::startSniffing() {

		static u_char* error;
		struct bpf_program program;

		if(_interface == NULL)
		{
			cout << "Undefined interface";
			Sniffer::_errorCode = -1;
			return -1;
		}

		_packetDescr = pcap_open_live(_interface->name, BUFSIZ,
					                 0, -1, _errbuf);
		if(_packetDescr == NULL) {
			cout << "Failed opening on interface. Error : " << _errbuf << endl;
			return -1;
		}

		// AFDX specific filter:
		// filter description : The packet must be of type IP with
		// udp on top of it whose checksum udp[6:2] is '0x0' (6 = position,
		// 2 = offset)
		pcap_compile(const_cast<pcap_t*>(_packetDescr), &program,
					"ip and udp", 1,
					 _netp);

		if (pcap_setfilter(const_cast<pcap_t*>(_packetDescr)
				, &program) == -1)
		{
			cout << "Failed setting the AFDX filter" << endl;
			_errorCode = -1;
			stopSniffing();
			return -1;
		}

		pcap_loop(const_cast<pcap_t*>(_packetDescr), -1,
				sniffCallback, error);
		return 0;
	}

	// code written temporarily for testing purposes.
	void Sniffer::monitorSniffer(void)
	{
		while(_packetDataVector.size() < 100 && _errorCode > -1)
		{
			cout << "Size of vector is " << dec
					<< static_cast<int>(_packetDataVector.size()) << endl;
			sleep(1);
		}

		Sniffer::stopSniffing();
	}

	int Sniffer::stopSniffing() {
		cout << "Stopping sniffer";
		pcap_breakloop(const_cast<pcap_t*>(_packetDescr));
		return 0;
	}

	Sniffer::~Sniffer() {
		// TODO Auto-generated destructor stub
	}
}
