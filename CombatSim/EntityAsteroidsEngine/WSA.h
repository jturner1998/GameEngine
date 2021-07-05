#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

class WSA
{
public:
	bool Init()
	{
		// Create version identifier
		WORD wVersionRequested = MAKEWORD(2, 0);

		// Startup windows sockets
		WSADATA wsaData;

		if (WSAStartup(wVersionRequested, &wsaData))
		{
			return false;
		}

		return true;
	}
};

