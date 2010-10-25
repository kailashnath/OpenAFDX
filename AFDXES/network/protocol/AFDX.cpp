/*
 * AFDX.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */


#include "AFDX.h"

namespace network
{
	namespace protocol
	{

		AFDX::AFDX() : _eth_type(ntohs(ETHERTYPE_IP)), _ip_ihl(5),
				_ip_version(4), _ip_tos(0), _ip_ttl(255), _ip_protocol(0x11),
				_udp_checksum(0x00), _payload(NULL)
		{
			memset(_datagram, 0, AFDX_BUFFER_SIZE);
		}

		void AFDX::build_raw_packet()
		{
			int sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
			int one = 1;
			const int* val = &one;
			if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
				std::cout << "Failed setting socket opt" << std::endl;
			std::cout << "Sock is : " << sock << std::endl;
			char datagram[4096];

			struct iphdr* ip_header = (struct iphdr* )(datagram );
			//struct tcphdr* tcp_header = (struct tcphdr*) (datagram + sizeof(struct iphdr));
			struct udphdr* udp_header = (struct udphdr*) (datagram + sizeof(struct iphdr));
			struct sockaddr_in sin;
			sin.sin_family = AF_INET;
			sin.sin_port = htons(40);
			sin.sin_addr.s_addr = inet_addr("10.1.33.0");

/*			ethhdr->ether_type = 0x0800;
			ether_addr* address = ether_aton("02:00:00:00:00:01");
			bcopy(address->ether_addr_octet, ethhdr->ether_shost, sizeof(address->ether_addr_octet));
			address = ether_aton("03:00:00:00:00:01");
			bcopy(address->ether_addr_octet, ethhdr->ether_dhost, sizeof(address->ether_addr_octet));
*/
			//ethhdr->ether_dhost = ether_aton("03:00:00:00:00:01")->ether_addr_octet;

			ip_header->ihl = 5;
			ip_header->version = 4;
			ip_header->tos = 0;
			ip_header->tot_len = sizeof (struct ip) + sizeof (struct udphdr) + 5;
			ip_header->id = htonl(1234);
			ip_header->frag_off = 0;
			ip_header->ttl = 255;
			ip_header->protocol = 0x11;
			ip_header->check = 0;
			ip_header->saddr = inet_addr("10.58.228.77");
			ip_header->daddr = sin.sin_addr.s_addr;

			/*tcp_header->source = htons(1234);
			tcp_header->dest = htons(85);
			tcp_header->seq = random();
			tcp_header->ack_seq = 0;
			tcp_header->doff = 0;
			tcp_header->syn = 1;
			tcp_header->window = htonl(65535);
			tcp_header->check = 0;
			tcp_header->urg_ptr = 0;
			*/
			udp_header->check = 0;
			udp_header->dest = htons(2525);
			udp_header->source = htons(4545);
			udp_header->len = htons(sizeof(struct udphdr) + 5);
			ip_header->check = network::protocol::csum(
					(unsigned short*) datagram, ip_header->tot_len >> 1);

			char* payload = datagram + ip_header->tot_len - 5;
			strcpy(payload, "kals");
			int count = 0;

			while(count < 100)
			{
				if(sendto(sock, datagram, ip_header->tot_len, 0, (const sockaddr*) &sin, sizeof(sin)) < 0)
					std::cout << "Error !" << std::endl;
				++count;
			}

		}

		void AFDX::build_packet()
		{
			int size_index = 0;

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
			ether_addr* address = ether_aton(_eth_src_mac);
			bcopy(address->ether_addr_octet, ethhdr->ether_shost,
					sizeof(address->ether_addr_octet));
			address = ether_aton(_eth_dst_mac);
			bcopy(address->ether_addr_octet, ethhdr->ether_dhost,
					sizeof(address->ether_addr_octet));

			// calculate the total length of the Datagram. This value goes
			// into the ip->len
			int ip_total_length = size_index - sizeof(struct ether_header);
			ip_total_length += strlen(_payload);

			// add ip details
			ip_header->ihl 	   = _ip_ihl;
			ip_header->version = _ip_version;
			ip_header->tos 	   = _ip_tos;
			ip_header->tot_len = htons(ip_total_length);
			ip_header->id 	   = htons(_ip_id);
			ip_header->frag_off = _ip_frag_off;
			ip_header->ttl 		= _ip_ttl;
			ip_header->protocol = _ip_protocol;
			ip_header->check 	= _ip_checksum;
			ip_header->saddr 	= inet_addr(_ip_saddr);
			ip_header->daddr 	= inet_addr(_ip_daddr);
			ip_header->check 	= network::protocol::csum(
					(unsigned short*) (_datagram + sizeof(struct ether_header)),
					ip_total_length >> 1);

			// add udp details
			udp_header->dest   = htons(_udp_dest);
			udp_header->source = htons(_udp_source);
			udp_header->check  = _udp_checksum;
			udp_header->len    = htons(sizeof(struct udphdr));

			Transmitter t(const_cast<char*>("eth0"), NULL);

			if(t.do_transmit(const_cast<u_char*>(_datagram),
					_iface, size_index, 100, true) < 0)
				std::cout << "Error !" << std::endl;
		}

		AFDX::~AFDX()
		{
			// TODO Auto-generated destructor stub
		}
	}
}
