#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma once


class SocketAddress
{
	sockaddr_in _sockAddr;

public:
	SocketAddress(const std::string& ip, int port)
	{
		_sockAddr.sin_family = AF_INET;
		_sockAddr.sin_port = htons(port);
		inet_pton(_sockAddr.sin_family, ip.c_str(), &_sockAddr.sin_addr);
	}

	int GetSize() const { return sizeof(sockaddr); }
	sockaddr_in* GetSockAddrIn() { return &_sockAddr; }

};

