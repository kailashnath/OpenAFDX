/*
 * Main.cpp
 *
 *  Created on: 11-Oct-2010
 *      Author: Kailashnath
 *      Email : kailashnathreddy@ymail.com or knr413@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <boost/thread.hpp>
#include <sys/types.h>
#include "headers/network/NetworkConfiguration.h"
#include "headers/network/Sniffer.h"
#include "headers/network/Reader.h"
#include "headers/parser/ICDParser.h"
#include "headers/config/VirtualLink.h"
#include "headers/commands/RSET.h"
#include "headers/network/protocol/AFDX.h"

using namespace std;
using namespace network;

const char* filename = "/media/439385db-7b6b-4585-a6ae-bd5553ca10d7/"
		"Releases/ITR-ES-003-RELEASE/captures/ITR-ES-003.cap";
const char* icd_file = "/home/robuntu/Releases/PythonScripts/Linux/ICD/"
		"newicd.csv";
//const char* icd_file = "/home/kailash/Github/ICD/newicd.csv";

int main(void)
{
	commands::RSET rset;
	parser::ICDParser parser(icd_file);
	parser.load_objects_from_icd();
	std::vector<config::VirtualLink> outputs =
			parser.get_objects(config::TYPE_OUTPUT);
	cout << "No of output vls = " << outputs.size() << endl;
	parser.cleanup();

	config::VirtualLink rst_vl = outputs[1];
	rst_vl._type_command = false;
	network::protocol::AFDX afdx(rst_vl);
	commands::command_string cmd;
	rset.build_command_str(cmd);
	afdx.build_packet(cmd);

	/*NetworkConfiguration nc;
	nc.show_user_options();
	Reader r(filename);
	r.print_details();

	if(nc.is_option_valid())
	{
		Sniffer sf(nc.get_selected_iface());
		boost::thread workerThread(Sniffer::start_sniffing);
		boost::thread monitor_snifferThread(Sniffer::monitor_sniffer);
		monitor_snifferThread.join();
	}
	*/
	cout << "Completed";
	return -1;
}
