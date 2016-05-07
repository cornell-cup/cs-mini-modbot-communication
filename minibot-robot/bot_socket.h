#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

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
	static int sendMotorControl();
};