#pragma once
#include "BaseClient/BaseClient.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

class UDPclient: public BaseClient {
public:
	UDPclient(): BaseClient() {
	}
	
	void Run() {
		if(!_connected) {
			std::cerr << "Client not connected!" << std::endl;
			return;
		}

		int bytesSent;
		int readBufferSize = _maxMessageLenght + 1;
		
		while(true) {
			struct sockaddr_in servaddr;

			std::cout << "Enter reqest: ";
			std::string request;// = "tcpdum11p tc2 p po3rt 450";
			std::getline(std::cin, request);

			if(request.length() > _maxMessageLenght) {
				request = request.substr(0, _maxMessageLenght);
			}

			bytesSent = sendto(
				_socketFD,
				request.c_str(),
				request.length() + 1,
				MSG_CONFIRM,
				(struct sockaddr*)&_stSockAddr,
				sizeof(struct sockaddr_in)
			);
		
			if (bytesSent < 0) {
				std::cerr << "Packet sending error!" << std::endl;
			}

			std::cout << "try to read" << std::endl;
			socklen_t *address_len = NULL;

			char readBuffer[readBufferSize];
			recvfrom(
				_socketFD,
				readBuffer,
				readBufferSize,
				MSG_WAITALL,
				(struct sockaddr*)&_stSockAddr,
				address_len
			);

			std::cout
				<< "Server response:"
				<< std::endl
				<< (std::string)readBuffer
				<< std::endl
			;
		}
	}
	~UDPclient() {
		close(_socketFD);
	}
private:
	void _CreateSocket() {
		_socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}
};