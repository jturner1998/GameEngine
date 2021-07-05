#pragma once
#include <iostream>
#include <winsock2.h>
#include "SocketAddress.h"

// TCP SERVER
#pragma comment(lib, "ws2_32.lib")
using namespace std;

class TCPAddress
{
protected:
	SOCKET _socket;

public:
	TCPAddress();
	TCPAddress(SOCKET s) : _socket(s) {}
	~TCPAddress();

	bool Connect(SocketAddress& address);
	bool Bind(SocketAddress& address);
	bool Listen();
	TCPAddress Accept();
	bool Send(const char* data, int size);
	bool Recieve(char* data, int size);



};
