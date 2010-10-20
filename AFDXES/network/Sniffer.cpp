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
	bpf_u_int32   Sniffer::_netp 	    = NULL;
	bpf_u_int32   Sniffer::_maskp 	    = NULL;
	int           Sniffer::_errorCode   = 0;

	struct in_addr 		  Sniffer::_addr;
	char 		   		  Sniffer::_errbuf[PCAP_ERRBUF_SIZE];

	// global static variable which holds the list of all
	// packets being captured.
	std::vector<const u_char*> common::packetDataVector;

	Sniffer::Sniffer(pcap_if_t* interface)
	{

		if(_packetDescr != NULL)
		{
			std::cout << "Sniffer already running !" << std::endl;
			return;
		}
		else if (interface == NULL)
		{
			std::cout << "Interface cannot be null" << std::endl;
			_errorCode = -1;
			return;
		}

		Sniffer::_interface = interface;
		std::cout << "Initializing sniffer on : " << Sniffer::_interface->name
                  << std::endl;

		if(pcap_lookupnet(Sniffer::_interface->name,
				&_netp, &_maskp, _errbuf) == -1)
		{
			std::cout << "Error : " << _errbuf << std::endl;
			_errorCode = -1;
		}
	}

	int Sniffer::print_iface_details()
	{
		char* net;
		char* mask;

		if(_netp == NULL || _maskp == NULL)
		{
			std::cout << "Sniffer was not initialized properly" << std::endl;
			_errorCode = -1;
			return -1;
		}

		_addr.s_addr = _netp;
		net = inet_ntoa(_addr);
		std::cout << "Network address is " << net << std::endl;

		_addr.s_addr = _maskp;
		mask = inet_ntoa(_addr);
		std::cout << "Mask address is " << net << std::endl;

		return 0;
	}



	int Sniffer::start_sniffing()
	{

		static u_char* error;
		struct bpf_program program;

		if(_interface == NULL)
		{
			std::cout << "Undefined interface";
			Sniffer::_errorCode = -1;
			return -1;
		}

		_packetDescr = pcap_open_live(_interface->name, BUFSIZ,
					                 0, -1, _errbuf);
		if( _packetDescr == NULL) {
			std::cout << "Failed opening on interface. Error : "
                      << _errbuf << std::endl;
			return -1;
		}

		// AFDX specific filter:
		// filter description : The packet must be of type IP with
		// udp on top of it whose checksum udp[6:2] is '0x0' (6 = position,
		// 2 = offset)
		// udp checksum filter : and udp[6:2] = 0x0
		// omitted temporarily for testing purposes
		pcap_compile(const_cast<pcap_t*>(_packetDescr), &program,
				common::kafdxFilterExperssion.c_str(), 1, _netp);

		if (pcap_setfilter(const_cast<pcap_t*>(_packetDescr), &program) == -1)
		{
			std::cout << "Failed setting the AFDX filter" << std::endl;
			_errorCode = -1;
			stop_sniffing();
			return -1;
		}

		pcap_loop(const_cast<pcap_t*>(_packetDescr), -1,
				common::pcapCallback, error);
		return 0;
	}

	int Sniffer::stop_sniffing()
	{
		std::cout << "Stopping sniffer" << std::endl;
		pcap_breakloop(const_cast<pcap_t*>(_packetDescr));
		return 0;
	}

	// code written temporarily for testing purposes.
	// TODO Delete this function. :)
	void Sniffer::monitor_sniffer(void)
	{
		while(true)
		{
			std::cout << "Vector size is : "
                      << common::packetDataVector.size() << std::endl;
			sleep(1);
		}

		Sniffer::stop_sniffing();
	}

	Sniffer::~Sniffer()
	{
		// make the vector available for OS
		// to redeem its memory
		common::packetDataVector.erase(common::packetDataVector.begin(),
				common::packetDataVector.end());
	}
}
