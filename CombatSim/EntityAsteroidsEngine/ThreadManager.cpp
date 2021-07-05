#include "ThreadManager.h"

const int ThreadManager::MAX_THREAD = 3;

ThreadManager::ThreadManager(int peer)
{
	_peer = peer;
}

ThreadManager::~ThreadManager()
{

}

void ThreadManager::Configure(string fileName)
{
	stringstream ss;
	string line;

	ifstream configuration(fileName + ".txt");

	if (!configuration)
	{
		return;
	}

	while (getline(configuration, line))
	{
		if (line == "Client" || line == "Server")
		{
			getline(configuration, line);
			
			_IP = line;

			getline(configuration, line);

			ss << line;
			ss >> _port;
		}
	}
}