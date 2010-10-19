/*
 * common.cpp
 *
 *  Created on: 14-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "common.h"

namespace network
{
	std::string common::kafdxFilterExperssion = "ip and udp";
	void common::pcapCallback(u_char* arg, const struct pcap_pkthdr* pcktHeader,
					  const u_char* data)
	{

		packetDataVector.push_back(data);

		int detIndex = 0;
		show_packet_details(pcktHeader);

		show_ether_details(
				reinterpret_cast<const struct ether_header*>(data));

		detIndex += sizeof(struct ether_header);
		// cast the data to ip header leaving the ether_header
		show_ip_details(reinterpret_cast<const struct iphdr*>(
				data + detIndex));

		detIndex += sizeof(struct iphdr);
		show_udp_details(reinterpret_cast<const struct udphdr*>(
				data + detIndex));

		detIndex += sizeof(struct udphdr);
		show_payload(data + detIndex);

	}

	void common::show_packet_details(const struct pcap_pkthdr* packet_header)
	{
		std::cout << "Length of the packet is : " << packet_header->len << std::endl;
		std::cout << "Received at : " << ctime(const_cast<const time_t*>(&packet_header->ts.tv_sec)) << std::endl;
	}

	void common::show_ether_details(const struct ether_header* ether_header)
	{
		uint16_t ethtype = ntohs(ether_header->ether_type);

		std::cout << "Ethernet type is hex : " << std::hex << ethtype << ", dec : "
			      << std::dec << static_cast<int>(ethtype) << std::endl;

		std::cout << "Source : " <<
				  ether_ntoa(reinterpret_cast<const struct ether_addr*>(
						(ether_header->ether_shost))) << std::endl;

		std::cout << "Destination : " <<
				  ether_ntoa(reinterpret_cast<const struct ether_addr*>(
						(ether_header->ether_dhost))) << std::endl;
	}

	void common::show_ip_details(const struct iphdr* ip_header)
	{
		std::cout << "IP protocol is : " << std::hex <<
				static_cast<int>(ip_header->protocol) << std::endl;
	}

	void common::show_udp_details(const struct udphdr* udp_header)
	{
		std::cout << "UDP source port is : " << std::dec
				<< htons(udp_header->source) << std::endl;
		std::cout << "UDP destination port is : " << std::dec
				<< htons(udp_header->dest) << std::endl;
		std::cout << "UDP Checksum is : " << std::dec <<
				htons(udp_header->check) << std::endl;
	}

	void common::show_payload(const u_char* data)
	{
		//char* payload = reinterpret_cast<char*>(const_cast<u_char*>(data));
		std::cout << data << std::endl;
	}
}
