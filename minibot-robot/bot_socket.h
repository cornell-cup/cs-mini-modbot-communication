#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

class FakeBlob;

class MinibotClient
{
private:
	const static char* IPADDRESS;
	const static int PORT;

	static WSADATA wsa;
	static SOCKET botSocket;
	static struct sockaddr_in botAddr;

public:
	static int setupBotSocket();
	static int closeBotSocket();
	static int sendMotorControl();
};