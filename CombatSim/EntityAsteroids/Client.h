#pragma once
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>

#include "WSA.h"
#include "SocketAddress.h"
#include "TCPAddress.h"

class Client
{
protected:
	char _peer;
	vector<thread> threadPool;
	static const int MAX_THREAD;

	Client(char peer, string IP, int port);
	~Client();

	void CreateSocket(string IP, int port);

	void Listen();

	void Transfer();



};

