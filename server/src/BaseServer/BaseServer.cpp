#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "BaseServer.hpp"
BaseServer::BaseServer() {
	_serverPort = -1;
}
void BaseServer::SetServerPort(int port) {
	_serverPort = port;
}

bool BaseServer::CreateConnection() {
	_connected = false;
	if(_serverPort < 0 || _serverPort > 65535) {
		std::cerr << "Error: correct port number (0 - 65535) needed" << std::endl;
		return false;
	}

	_CreateSocket();
	
	if (_socketFD == -1) {
		std::cerr << "Error: sock creation err" << std::endl;
		return false;
	}

	memset(&_stSockAddr, 0, sizeof (_stSockAddr));
	
	_stSockAddr.sin_family = AF_INET;
	_stSockAddr.sin_port = htons(_serverPort);
	_stSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(_socketFD, (struct sockaddr*)&_stSockAddr, sizeof(struct sockaddr)) < 0) {
		std::cerr << "Error: bind err"<< std::endl;
		close(_socketFD);
		return false;
	}
	if(!_StartListen()) {
		std::cerr << "Error: socket listening failed" << std::endl;
		close(_socketFD);
		return false;
	}

	_connected = true;
	return true;
}


BaseServer::~BaseServer() {
	close(_socketFD);
}

bool BaseServer::_StartListen() {
	return true;
}