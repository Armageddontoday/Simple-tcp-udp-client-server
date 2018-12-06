#pragma once

#include "RequestHandler/RequestHandler.hpp"
#include "BaseServer/BaseServer.hpp"

class UDPserver: public BaseServer {
	
public:
	UDPserver() : BaseServer() {
	}

	void Run() {
		if(!_connected) {
			std::cerr << "Server not connected!" << std::endl;
			return;
		}

		int readBuffSize = _maxMessageLenght + 1;
		char readBuffer[readBuffSize];

		while(true)
		{
			std::cout << "Wainting for incoming request..." << std::endl;
			
			struct sockaddr_in client_addr;
			socklen_t clientAddrLen;
			memset(&client_addr, 0, sizeof(client_addr)); 
			
			//request reading
			int bytesReaded = recvfrom(
				_socketFD,
				(char*)readBuffer,
				_maxMessageLenght,
				MSG_WAITALL,
				(struct sockaddr*)&client_addr,
				&clientAddrLen
			);

			if(bytesReaded < 0) {
				std::cerr << "Request packet reading error!" << std::endl;
				continue;
			}

			readBuffer[bytesReaded] = '\0';
			std::cout << "Got request:" << (std::string)readBuffer << std::endl;
			std::string answer = _handler.GenerateReply(readBuffer);

			//reply sending
			int bytesSent = sendto(
				_socketFD,
				answer.c_str(),
				answer.length() + 1,
				0,
				(sockaddr *)&client_addr,
				sizeof(client_addr)
			);
			
			if (bytesSent < 0) {
				std::cerr << "Reply packet sending error!" << std::endl;
			}
		}
	}
	~UDPserver(){
		close(_socketFD);
	}
private:
	void _CreateSocket() {
		_socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	}
};