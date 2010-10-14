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

	Sniffer::Sniffer(pcap_if_t* interface)
	{

		if(NULL != _packetDescr)
		{
			cout << "Sniffer already running !" << endl;
			return;
		}
		else if (NULL == interface)
		{
			cout << "Interface cannot be null" << endl;
			_errorCode = -1;
			return;
		}

		Sniffer::_interface = interface;
		cout << "Initializing sniffer on : " << Sniffer::_interface->name
				<< endl;

		if(-1 == pcap_lookupnet(Sniffer::_interface->name,
				&_netp, &_maskp, _errbuf))
		{
			cout << "Error : " << _errbuf << endl;
			_errorCode = -1;
		}
	}

	int Sniffer::printInterfaceDetails()
	{
		char* net;
		char* mask;

		if(NULL == _netp || NULL == _maskp)
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



	int Sniffer::startSniffing() {

		static u_char* error;
		struct bpf_program program;

		if(NULL == _interface)
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
		// udp checksum filter : and udp[6:2] = 0x0
		// omitted temporarily for testing purposes
		pcap_compile(const_cast<pcap_t*>(_packetDescr), &program,
					"ip and tcp", 1, _netp);

		if (-1 == pcap_setfilter(const_cast<pcap_t*>(_packetDescr), &program))
		{
			cout << "Failed setting the AFDX filter" << endl;
			_errorCode = -1;
			stopSniffing();
			return -1;
		}

		pcap_loop(const_cast<pcap_t*>(_packetDescr), -1,
				pcapCallback, error);
		return 0;
	}

	// code written temporarily for testing purposes.
	void Sniffer::monitorSniffer(void)
	{
		while(packetDataVector.size() < 100 && _errorCode > -1)
		{
			cout << "Size of vector is " << dec
					<< static_cast<int>(packetDataVector.size()) << endl;
			sleep(1);
		}

		Sniffer::stopSniffing();
	}

	const pcap_t* Sniffer::getPcapHandler(void)
	{
		return _packetDescr;
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
