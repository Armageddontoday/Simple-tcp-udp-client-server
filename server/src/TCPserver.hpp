#pragma once
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <iostream>
#include "RequestHandler/RequestHandler.hpp"
#include "BaseServer/BaseServer.hpp"

class TCPserver : public BaseServer{
	public:
		TCPserver() : BaseServer() {

		}
		void Run() {
			std::cout << "Start reading" << std::endl;
	
			while (true) {
				int connectedFD = accept(_socketFD, 0, 0);
				if (connectedFD < 0) {
					std::cerr << "Connection accept error." << std::endl;
					close(_socketFD);
					return;
				}
				std::cout << "New client connected!" << std::endl;
				
				int readBuffSize = _maxMessageLenght + 1;
				char readBuffer[readBuffSize];

				int getBytes = read(connectedFD, readBuffer, readBuffSize);
				readBuffer[getBytes] = '\0';
				std::cout << "Got request:" << readBuffer << std::endl << std::endl;
				
				std::string answer = _handler.GenerateReply(readBuffer);
				write(connectedFD, answer.c_str(), answer.length() + 1);
				
				shutdown(connectedFD, SHUT_RDWR);
			}
		}
		~TCPserver() {
			close(_socketFD);
		}
private:
	void _CreateSocket() {
		_socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	bool _StartListen() {
		if (listen(_socketFD, 10) == -1) {
			std::cerr << "Socket listen error." << std::endl;
			return false;
		}
		return true;
	}
};