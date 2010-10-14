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

	void pcapCallback(u_char* arg, const struct pcap_pkthdr* pcktHeader,
						  const u_char* data) {

				packetDataVector.push_back(data);

				int detIndex = 0;
				showPacketDetails(pcktHeader);

				showEthernetDetails(
						reinterpret_cast<const struct ether_header*>(data));

				detIndex += sizeof(struct ether_header);
				// cast the data to ip header leaving the ether_header
				showIPDetails(reinterpret_cast<const struct iphdr*>(
						data + detIndex));

				detIndex += sizeof(struct iphdr);
				showUDPDetails(reinterpret_cast<const struct udphdr*>(
						data + detIndex));

				detIndex += sizeof(struct udphdr);
				showPayload(data + detIndex);

		}
	void showPacketDetails(const struct pcap_pkthdr* packet_header)
	{
		cout << "Length of the packet is : " << packet_header->len << endl;
		cout << "Received at : " << ctime(const_cast<const time_t*>(&packet_header->ts.tv_sec)) << endl;
	}

	void showEthernetDetails(const struct ether_header* ether_header)
	{
		uint16_t ethtype = ntohs(ether_header->ether_type);

		cout << "Ethernet type is hex : " << hex << ethtype << ", dec : "
				<< dec << static_cast<int>(ethtype) << endl;

		cout << "Source : " <<
				ether_ntoa(reinterpret_cast<const struct ether_addr*>(
						(ether_header->ether_shost))) << endl;

		cout << "Destination : " <<
				ether_ntoa(reinterpret_cast<const struct ether_addr*>(
						(ether_header->ether_dhost))) << endl;
	}

	void showIPDetails(const struct iphdr* ip_header)
	{
		cout << "IP protocol is : " << hex << static_cast<int>(ip_header->protocol) << endl;
	}

	void showUDPDetails(const struct udphdr* udp_header)
	{
		cout << "UDP source port is : " << dec << htons(udp_header->source) << endl;
		cout << "UDP destination port is : " << dec << htons(udp_header->dest) << endl;
		cout << "UDP Checksum is : " << dec << htons(udp_header->check) << endl;
	}

	void showPayload(const u_char* data)
	{
		//char* payload = reinterpret_cast<char*>(const_cast<u_char*>(data));
		cout << data << endl;
	}
}
