/*
 * AFDX.h
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */


#ifndef AFDX_H_
#define AFDX_H_

#include <iostream>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netinet/udp.h>

#include "../NetworkConfiguration.h"
#include "../Transmitter.h"
#include "common.h"

#define AFDX_BUFFER_SIZE 4096

namespace network
{
	namespace protocol
	{
		class AFDX {
		public:
			AFDX();
			void build_net_packet(void);
			void build_packet(void);
			void build_raw_packet(void);
			virtual ~AFDX();

		protected:
			char* _eth_src_mac;
			char* _eth_dst_mac;
			u_int16_t _eth_type;

			unsigned int _ip_ihl;
			unsigned int _ip_version;
			u_int8_t _ip_tos;
			u_int8_t _ip_ttl;
			u_int8_t _ip_protocol;
			u_int16_t _ip_tot_len;
			u_int16_t _ip_id;
			u_int16_t _ip_frag_off;
			u_int16_t _ip_checksum;
			const char* _ip_saddr;
			const char* _ip_daddr;

			u_int16_t _udp_source;
     		u_int16_t _udp_dest;
			u_int16_t _udp_len;
			u_int16_t _udp_checksum;

			char* _payload;
			short _iface;
		private:
			u_char _datagram[AFDX_BUFFER_SIZE];
		};
	}
}
#endif /* AFDX_H_ */
