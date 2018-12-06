#include <iostream>
#include <algorithm>
#include <string>

#include "TCPclient.hpp"
#include "UDPclient.hpp"

void PrintHelp() {
	std::cout
		<< "To run client you need to specify next parameters:" << std::endl
		<< "connection type  : tcp/udp" <<  std::endl
		<< "server ip,   e.g.: 192.168.0.100" <<  std::endl 
		<< "server port, e.g.: 12345" <<  std::endl
	;
}

int main(int argc, char *argv[]) {
	if(argc != 4) {
		PrintHelp();
		return 0;
	}

	std::string connectionType = argv[1];
	std::transform(connectionType.begin(), connectionType.end(), connectionType.begin(), ::tolower);
	if(connectionType != "tcp" && connectionType != "udp") {
		std::cerr << "Error:Wrong connection type! Must be tcp/udp!" << std::endl;
		PrintHelp();
		return 0;
	}

	BaseClient *currentClient = NULL;
	if(connectionType == "tcp") {
		currentClient = new TCPclient();
	} else if (connectionType == "udp") {
		currentClient = new UDPclient();
	} else {
		std::cerr << "Protocol type error!" << std::endl;
		return 1;
	}
	
	if(currentClient == NULL) {
		std::cerr << "Client creation error!" << std::endl;
		return 1;
	}

	currentClient->SetServIp(argv[2]);
	currentClient->SetServerPort(std::atoi(argv[3]));
	currentClient->CreateConnection();
	currentClient->Run();
	delete currentClient;

	return 0;
}