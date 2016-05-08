#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>

#include "control_pkt.h"

#pragma comment(lib, "ws2_32.lib")

class FakeBlob;

class MinibotServer
{
private:
	const static char* IPADDRESS;
	const static int PORT;

	static int botSocket;
	static struct sockaddr_in botAddr;

public:
	static int setupBotSocket();
	static int server();
	static int closeBotSocket();
	static int sendMotorControl(Control *pkt);
};
