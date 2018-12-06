#include <string>       // std::string
#include <iostream>     // std::cout

#include <algorithm>

#include "TCPserver.hpp"
#include "UDPserver.hpp"
#include "BaseServer/BaseServer.hpp"

using namespace std;


void PrintHelp() {
	std::cout
		<< "To run client you need to specify next parameters:" << std::endl
		<< "connection type: tcp/udp" <<  std::endl
		<< "port to operate e.g. 1100" <<  std::endl 
	;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		PrintHelp();
		return 1;
	}

	std::string connectionType = argv[1];
	std::transform(connectionType.begin(), connectionType.end(), connectionType.begin(), ::tolower);
	if(connectionType != "tcp" && connectionType != "udp") {
		std::cerr << "Error: wrong connection type! Must be tcp/udp!" << std::endl;
		PrintHelp();
		return 1;
	}
	
	BaseServer *currentServer = NULL;

	if(connectionType == "tcp") {
		currentServer = new TCPserver();
	} else if (connectionType == "udp") {
		currentServer = new UDPserver();
	} else {
		std::cerr << "Protocol type error!" << std::endl;
		return 1;
	}

	if(currentServer == NULL) {
		std::cerr << "Server creation error!" << std::endl;
		return 1;
	}

	currentServer->SetServerPort(std::atoi(argv[2]));
	currentServer->CreateConnection();
	currentServer->Run();
	delete currentServer;
	return 0;
}