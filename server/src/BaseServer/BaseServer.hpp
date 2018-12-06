#pragma once
#include <netinet/in.h>

#include <string>
#include <iostream>
#include "../RequestHandler/RequestHandler.hpp"

//base class for tcp/udp synchronous servers, set port number before connection attempt
class BaseServer {
public:
	BaseServer();
	void SetServerPort(int port);

	//creates socket connection, using _CreateSocket() & _StartListen()
	bool CreateConnection();

	//main loop for sending/reading messages
	virtual void Run() = 0;

	virtual ~BaseServer();
protected:
	
	struct sockaddr_in _stSockAddr;
	socklen_t address_len;

	int _socketFD;
	int _serverPort;

	bool _connected;
	const int _maxMessageLenght = 1023;

	RequestHandler _handler;

	//socket creation for tcp/udp is different, it's necessary to specify it
	virtual void _CreateSocket() = 0;
	//specify for tcp
	virtual bool _StartListen();
};