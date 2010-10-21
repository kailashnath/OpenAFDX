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

#include "network/NetworkConfiguration.h"
#include "network/Sniffer.h"
#include "network/Reader.h"
#include "parser/ICDParser.h"

using namespace std;
using namespace network;

const char* filename = "/media/439385db-7b6b-4585-a6ae-bd5553ca10d7/"
		"Releases/ITR-ES-003-RELEASE/captures/ITR-ES-003.cap";

int main(void)
{
	parser::ICDParser icd_parser("/home/robuntu/Releases/PythonScripts/Linux/ICD/CPIOM_ICDcompleted.csv");
	cout << icd_parser.is_icd_valid();
	icd_parser.load_objects_from_icd();
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
