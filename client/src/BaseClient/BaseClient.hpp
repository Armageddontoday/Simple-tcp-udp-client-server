#pragma once
#include <netinet/in.h>
#include <string>

//base client contains required server addr&port info, creates socket
class BaseClient {
public:
	BaseClient();

	void SetServIp(std::string ip);

	void SetServerPort(int port);

	//creates socket connection, using _CreateSocket()
	bool CreateConnection();

	//main loop for sending/reading messages
	virtual void Run() = 0;

	virtual ~BaseClient();
protected:
	struct sockaddr_in _stSockAddr;
	int _socketFD;

	std::string _serverIP;
	int _serverPort;
	
	bool _connected;

	const int _maxMessageLenght = 1023;
	
	//socket creation for tcp/udp is different, it's necessary to specify it
	virtual void _CreateSocket() = 0;
};