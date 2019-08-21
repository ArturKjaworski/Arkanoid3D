#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>

#include <string>
#include <vector>

class Network
{
public:
	Network();
	~Network();

	static Network& GetInstance();

	WSAData wsaData;
	WORD version = 0x202;
	SOCKET sock;
	fd_set rset;
	HANDLE event;

	SOCKADDR_IN local_address;

	enum EConnectionType
	{
		NONE,
		Server,
		Client
	};
	EConnectionType type = EConnectionType::NONE;

	std::vector<SOCKADDR_IN> clients;
	std::string serverAddress = "";

	static const int SOCKET_BUFFER_SIZE = 1000;
	char buffer[SOCKET_BUFFER_SIZE];

	bool Init();
	void InitServer();
	void InitClient();

	void SetServerAddress(std::string address);

	std::string recv();
	void sendToServer(const std::string input);
	void sendToAll(const std::string input);
};
