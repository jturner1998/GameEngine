#include "TCPAddress.h"

TCPAddress::TCPAddress()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET) {
		cerr << "Create socket failed with " << WSAGetLastError() << endl;
	}
}

TCPAddress::~TCPAddress()
{
	shutdown(_socket, SD_BOTH);
	closesocket(_socket);
}

bool TCPAddress::Connect(SocketAddress& address)
{
	if (connect(_socket, (sockaddr*)address.GetSockAddrIn(), address.GetSize()) == SOCKET_ERROR)
	{
		cerr << "Connect() to peer failed with " << WSAGetLastError() << "\n";
		return false;
	}
	return true;
}

bool TCPAddress::Bind(SocketAddress& address)
{
	if (bind(_socket, (sockaddr*)address.GetSockAddrIn(), address.GetSize()) == SOCKET_ERROR)
	{
		cerr << "Bind failed with " << WSAGetLastError() << "\n";
		return false;
	}
	return true;
}

bool TCPAddress::Listen()
{
	if (listen(_socket, 5) == SOCKET_ERROR)
	{
		cerr << "Listen failed with " << WSAGetLastError() << "\n";
		return false;
	}
	return true;
}

TCPAddress TCPAddress::Accept()
{
	SOCKET s = accept(_socket, NULL, NULL);
	if (s == INVALID_SOCKET)
	{
		cerr << "Accept failed with " << WSAGetLastError() << "\n";
	}
	return TCPAddress(s);
}

bool TCPAddress::Send(const char* data, int size)
{
	if (send(_socket, data, size, 0) == SOCKET_ERROR)
	{
		cerr << "Send failed with " << WSAGetLastError() << "\n";
		return false;
	}
	return true;
}

bool TCPAddress::Recieve(char* data, int size)
{
	if (recv(_socket, data, size, 0) == SOCKET_ERROR)
	{
		cerr << "Receive failed with " << WSAGetLastError() << "\n";
		return false;
	}
	return true;
}