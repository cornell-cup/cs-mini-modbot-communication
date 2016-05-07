#include "bot_socket.h"
#include "stdafx.h"

const char * MinibotClient::IPADDRESS = "127.0.0.1";
const int MinibotClient::PORT = 607;

WSADATA MinibotClient::wsa;
SOCKET MinibotClient::botSocket;
struct sockaddr_in MinibotClient::botAddr;

int MinibotClient::setupBotSocket()
{
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	if ((botSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("Could not create socket.\n");
		return -1;
	}
	else
	{
		printf("Socket created.\n");
	}

	botAddr.sin_family = AF_INET;
	botAddr.sin_addr.s_addr = inet_addr(IPADDRESS);
	botAddr.sin_port = htons(PORT);

	if (connect(botSocket, (SOCKADDR *)&botAddr, sizeof(botAddr)) == SOCKET_ERROR)
	{
		printf("Connection error.\n");
		return -1;
	}
	else
	{
		printf("Connected.\n");
	}

	return 0;
}

int MinibotClient::closeBotSocket()
{
	closesocket(botSocket);
	WSACleanup();

	return 0;
}

int MinibotClient::sendMotorControl()
{
	char data[68];


	if (send(botSocket, (char*)&data, sizeof(data), 0) < 0)
	{
		printf("Send failed.\n");
		return -1;
	}
	else
	{
		printf("Sent.\n");
	}

	return 0;
}