#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "BaseClient.hpp"

BaseClient::BaseClient()
{
	_socketFD = -1;
	_connected = false;

	memset(&_stSockAddr, 0, sizeof(_stSockAddr));

	_serverIP.clear();
	_serverPort = -1;
}

void BaseClient::SetServIp(std::string ip) {
	_serverIP = ip;
}

void BaseClient::SetServerPort(int port) {
	_serverPort = port;
}

bool BaseClient::CreateConnection() {
	_connected = false;
	if(_serverIP.empty() || _serverPort < 0 || _serverPort > 65535) {
		std::cerr << "Server IP and correct port (0 - 65535) are needed!" << std::endl;
		return false;
	}
	
	_CreateSocket();

	if (_socketFD == -1) {
		std::cerr << "Socket creation error" << std::endl;
		return false;
	}

	memset(&_stSockAddr, 0, sizeof(_stSockAddr));

	_stSockAddr.sin_family = AF_INET;
	_stSockAddr.sin_port = htons(_serverPort);
	_stSockAddr.sin_addr.s_addr = INADDR_ANY;

	if (inet_pton(AF_INET, _serverIP.c_str(), &_stSockAddr.sin_addr) < 1) {
		std::cerr << "Incorrect server address:" << _serverIP << std::endl;
		close(_socketFD);
		return false;
	}

	_connected = true;
	std::cout << "Connected to " << _serverIP << ":" << _serverPort << std::endl;
	return _connected;
}

BaseClient::~BaseClient() {
	close(_socketFD);
}