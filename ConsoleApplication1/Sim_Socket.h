#include "stdafx.h"

class FakeBlob;

class SimulationClient
{
private:
	const static char* IPADDRESS;
	const static int PORT;

	static WSADATA wsa;
	static SOCKET simSocket;
	static struct sockaddr_in simAddr;

public:
	static int setupSimSocket();
	static int closeSimSocket();
	static int sendVisionBlob(FakeBlob const & blob);
};