#include "pch.h"

#include "Network.h"

#include <iostream>
#include <thread>

#define PORT 9999

Network::Network()
{
}


Network::~Network()
{
	closesocket(sock);
	clients.clear();
	WSACleanup();
}

Network& Network::GetInstance()
{
	 static Network instance;
	 return instance; 
};

bool Network::Init()
{
	if (type != EConnectionType::NONE)
		return false;

	if (WSAStartup(version, &wsaData) != 0)
	{
		std::cout << "Error on WSAStartup" << WSAGetLastError() << std::endl;
		return false;
	}

	//Create socket
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);		//IPv4, UDP
	if (sock == INVALID_SOCKET)
	{
		std::cout << std::endl << "Error on create socket" << WSAGetLastError() << std::endl;
		return false;
	}

	DWORD nonBlock = 1;
	::ioctlsocket(sock, FIONBIO, &nonBlock);

	return true;
}

void Network::InitServer()
{
	if (!Init())
		return;
	
	//bind socket
	local_address.sin_family = AF_INET;
	local_address.sin_port = htons(PORT);
	local_address.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (SOCKADDR*)&local_address, sizeof(local_address)) == SOCKET_ERROR)
	{
		std::cout << std::endl << "Error in binding socket: " << WSAGetLastError() << std::endl;
		return;
	}
	std::cout << std::endl << "Server inited" << std::endl;

	type = EConnectionType::Server;
}

void Network::InitClient()
{
	if (!Init())
		return;

	type = EConnectionType::Client;
	sendToServer("cc");
	std::cout << std::endl << "Client inited" << std::endl;
}

void Network::SetServerAddress(std::string address)
{
	serverAddress = address;
}

std::string Network::recv()
{
	int flags = 0;
	SOCKADDR_IN from;
	int from_size = sizeof(from);

	int bytes_received = recvfrom(sock, buffer, SOCKET_BUFFER_SIZE, flags, (SOCKADDR*)&from, &from_size);

	if (bytes_received == 0)
		return "";

	if (bytes_received == SOCKET_ERROR)
	{
		return "";
	}
	else
	{
		buffer[bytes_received] = 0;
	}

	if (std::strcmp(buffer, "cc") == 0)
	{
		clients.push_back(from);
	}

	if (std::strcmp(buffer, "quit") == 0)
	{
		for (auto iter = clients.begin(); iter != clients.end(); ++iter)
			if (((*iter).sin_addr.s_addr == from.sin_addr.s_addr) && ((*iter).sin_port == from.sin_port))
				clients.erase(iter);
	}
	return std::string(buffer);
}

void Network::sendToServer(const std::string msg)
{
	SOCKADDR_IN server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.S_un.S_addr = inet_addr(serverAddress.c_str());

	int flags = 0;
	if (sendto(sock, msg.c_str(), msg.length(), flags, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
	{
		return;
	}
}

void Network::sendToAll(const std::string msg)
{
	for (SOCKADDR_IN server_address : clients)
	{
		int flags = 0;
		if (sendto(sock, msg.c_str(), msg.length(), flags, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
		{
			std::cout << std::endl << "sendto failed:" << WSAGetLastError() << std::endl;
			return;
		}
	}
}
