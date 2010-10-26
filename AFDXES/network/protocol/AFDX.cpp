/*
 * AFDX.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include "../../headers/network/protocol/AFDX.h"

namespace network
{
	namespace protocol
	{

		AFDX::AFDX()
		{
			init();
		}

		AFDX::AFDX(config::VirtualLink& vl)
		{
			init();
			_eth_src_mac = "03:00:00:00:00:02";
			_eth_dst_mac = "02:00:00:00:00:05";
			_ip_daddr = vl._dst_ip;
			_ip_saddr = vl._src_ip;
			_ip_id = random();
			_udp_dest = vl._dst_udp;
			_udp_source = vl._src_udp;
			_iface = network::NetworkConfiguration::NETWORK_A;
		}

		void AFDX::init()
		{
			_eth_type = ntohs(ETHERTYPE_IP);
			_ip_ihl = 5;
			_ip_version = 4;
			_ip_tos = 0;
			_ip_ttl = 255;
			_ip_protocol = 0x11;
			_udp_checksum = 0x00;

			memset(_datagram, 0, AFDX_BUFFER_SIZE);
		}

		void AFDX::build_packet(commands::command_string& data_payload)
		{
			int size_index = 0;
			int payload_size = data_payload.length;
			std::cout << "Data" << payload_size << std::endl;

			struct ether_header* ethhdr =
					(struct ether_header*) _datagram;
			size_index = sizeof(struct ether_header);

			struct iphdr* ip_header =
					(struct iphdr* )(_datagram + size_index);
			size_index += sizeof(struct iphdr);

			struct udphdr* udp_header =
					(struct udphdr*)(_datagram + size_index);
			size_index += sizeof(struct udphdr);

			// add ethernet details
			ethhdr->ether_type = ntohs(ETHERTYPE_IP);
			ether_addr* address = ether_aton(_eth_src_mac.c_str());
			bcopy(address->ether_addr_octet, ethhdr->ether_shost,
					sizeof(address->ether_addr_octet));
			address = ether_aton(_eth_dst_mac.c_str());
			bcopy(address->ether_addr_octet, ethhdr->ether_dhost,
					sizeof(address->ether_addr_octet));

			// calculate the total length of the Datagram. This value goes
			// into the ip->len
			int ip_total_length = size_index - sizeof(struct ether_header);

			// add ip details
			ip_header->ihl 	   = _ip_ihl;
			ip_header->version = _ip_version;
			ip_header->tos 	   = _ip_tos;
			ip_header->tot_len = htons(ip_total_length + payload_size);
			ip_header->id 	   = htons(_ip_id);
			ip_header->frag_off = _ip_frag_off;
			ip_header->ttl 		= _ip_ttl;
			ip_header->protocol = _ip_protocol;
			ip_header->check 	= _ip_checksum;
			ip_header->saddr 	= inet_addr(_ip_saddr.c_str());
			ip_header->daddr 	= inet_addr(_ip_daddr.c_str());
			ip_header->check 	= network::csum(
					(unsigned short*) (_datagram + sizeof(struct ether_header)),
					ip_total_length >> 1);

			// add udp details
			udp_header->dest   = htons(_udp_dest);
			udp_header->source = htons(_udp_source);
			udp_header->check  = _udp_checksum;
			udp_header->len    = htons(sizeof(struct udphdr) + payload_size);
			std::cout << "Payload size is" << payload_size << std::endl;

			bcopy(data_payload.data, _datagram + size_index, payload_size );
			size_index += payload_size;

			network::Transmitter t(const_cast<char*>("wlan0"), NULL);

			if(t.do_transmit(const_cast<u_char*>(_datagram), size_index,
					_iface, 5, true) < 0)
				std::cout << "Error !" << std::endl;
		}

		AFDX::~AFDX()
		{
			// TODO Auto-generated destructor stub
		}
	}
}
