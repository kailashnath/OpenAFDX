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

			_eth_src_mac = SRC_MAC;

			if(vl._type_command)
			{
				_eth_dst_mac = DST_MAC;
				_ip_saddr 	 = TE_IP;
				_ip_daddr 	 = ES_IP;
				_udp_source  = UDP_SRC;
				_udp_dest	 = UDP_DST;
			}
			else
			{
				_eth_dst_mac = vl._dst_mac;
				_ip_daddr 	 = vl._dst_ip;
				_ip_saddr 	 = vl._src_ip;
				_udp_dest 	 = vl._dst_udp;
				_udp_source  = vl._src_udp;
			}
			_ip_id = random();
			_iface = network::NetworkConfiguration::NETWORK_A;
		}

		void AFDX::init()
		{
			_eth_type = ntohs(ETHERTYPE_IP);
			_ip_ihl 	   = 5;
			_ip_version    = 4;
			_ip_tos 	   = 0;
			_ip_ttl 	   = 255;
			_ip_protocol   = 0x11;
			_udp_checksum  = 0x00;
			_datagram_size = 0;
			memset(_datagram, 0, AFDX_BUFFER_SIZE);
		}

		void AFDX::build_packet(commands::command_string& data_payload)
		{
			int payload_size = data_payload.length;
			int padding_size = 0;

			if(payload_size < 17)
				padding_size = 17 - payload_size;

			struct ether_header* ethhdr =
					(struct ether_header*) _datagram;
			_datagram_size = sizeof(struct ether_header);

			struct iphdr* ip_header =
					(struct iphdr* )(_datagram + _datagram_size);
			_datagram_size += sizeof(struct iphdr);

			struct udphdr* udp_header =
					(struct udphdr*)(_datagram + _datagram_size);
			_datagram_size += sizeof(struct udphdr);

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
			int ip_total_length = _datagram_size - sizeof(struct ether_header);

			// add ip details
			ip_header->ihl 	    = _ip_ihl;
			ip_header->version  = _ip_version;
			ip_header->tos 	    = _ip_tos;
			ip_header->tot_len  = htons(ip_total_length + payload_size);
			ip_header->id 	    = htons(_ip_id);
			ip_header->frag_off = _ip_frag_off;
			ip_header->ttl 		= _ip_ttl;
			ip_header->protocol = _ip_protocol;
			ip_header->check 	= _ip_checksum;
			ip_header->saddr 	= inet_addr(_ip_saddr.c_str());
			ip_header->daddr 	= inet_addr(_ip_daddr.c_str());
			ip_header->check 	= network::protocol::csum(
					reinterpret_cast<unsigned short*> (_datagram + sizeof(struct ether_header)),
					ip_total_length);

			// add udp details
			udp_header->dest   = htons(_udp_dest);
			udp_header->source = htons(_udp_source);
			udp_header->check  = _udp_checksum;
			udp_header->len    = htons(sizeof(struct udphdr) + payload_size);

			bcopy(data_payload.data, _datagram + _datagram_size, payload_size );
			_datagram_size += payload_size;

			// this part takes care of padding part for AFDX
			if(padding_size > 0)
			{
				unsigned char padding[padding_size];
				memset(padding, 0x00, padding_size);
				bcopy(padding, _datagram + _datagram_size, padding_size);
				_datagram_size += padding_size;
			}

			// this part takes care of adding the packet sequence number
			{
				_datagram[_datagram_size] =	config::SequenceHandler::get_vl_sn(1);
				_datagram_size += 1;
			}

		}

		void AFDX::send()
		{
			network::Transmitter tx(const_cast<char*>("eth0"), NULL);
			if(tx.do_transmit(const_cast<u_char*>(_datagram), _datagram_size,
								_iface, 5, true) < 0)
			std::cout << "Error !" << std::endl;

		}

		AFDX::~AFDX()
		{
			// TODO Auto-generated destructor stub
		}
	}
}
