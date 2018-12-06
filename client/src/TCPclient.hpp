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

class TCPclient: public BaseClient {
public:
	TCPclient() : BaseClient() {
	}

	void Run() {
		if(!_connected) {
			std::cerr << "Client not connected!" << std::endl;
			return;
		}

		if (connect(_socketFD, (struct sockaddr*) &_stSockAddr, sizeof (_stSockAddr)) == -1) {
			std::cerr << "Tcp connection opening error!" << std::endl;
			close(_socketFD);
			return;
		}
		
		int bytesSent;
		int readBufferSize = _maxMessageLenght + 1;

		while(true) {
			std::string request;
			std::cout << "Enter reqest: ";
			std::getline(std::cin, request);
			if(request.length() > _maxMessageLenght) {
				request = request.substr(0, _maxMessageLenght);
			}
			if(request == "exit") {
				break;
			}
			bytesSent = write(_socketFD, request.c_str(), request.length() + 1);
			if (bytesSent < 0) {
				std::cerr << "Packet sending error!" << std::endl;
				continue;
			}

			request.clear();

			char readBuffer[readBufferSize];
			int bytesReaded = read(_socketFD, readBuffer, readBufferSize);
			
			if(bytesReaded < 0) {
				std::cerr << "Reply packet reading error!" << std::endl;
				continue;
			}

			readBuffer[bytesReaded] = '\0';
			
			std::cout
				<< "Server response:"
				<< std::endl
				<< (std::string)readBuffer
				<< std::endl
				<< std::endl
			;
		}
	}

	~TCPclient() {
		close(_socketFD);
	}
private:
	void _CreateSocket() {
		_socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

};