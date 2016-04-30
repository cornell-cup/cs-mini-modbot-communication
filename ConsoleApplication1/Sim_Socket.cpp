#include "stdafx.h"

const char * SimulationClient::IPADDRESS = "127.0.0.1";
const int SimulationClient::PORT = 607;

WSADATA SimulationClient::wsa;
SOCKET SimulationClient::simSocket;
struct sockaddr_in SimulationClient::simAddr;

int SimulationClient::setupSimSocket()
{
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	if ((simSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("Could not create socket.\n");
		return -1;
	}
	else
	{
		printf("Socket created.\n");
	}

	simAddr.sin_family = AF_INET;
	simAddr.sin_addr.s_addr = inet_addr(IPADDRESS);
	simAddr.sin_port = htons(PORT);

	if (connect(simSocket, (SOCKADDR *)&simAddr, sizeof(simAddr)) == SOCKET_ERROR)
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

int SimulationClient::closeSimSocket()
{
	closesocket(simSocket);
	WSACleanup();

	return 0;
}

int SimulationClient::sendVisionBlob(FakeBlob const & blob)
{
	char data[68];
	int * i;
	double * d;

	i = (int*)data;
	*i++ = blob.id;

	d = (double*)i;
	*d++ = blob.time;
	*d++ = blob.x;
	*d++ = blob.y;

	i = (int*)d;
	*i++ = blob.innerColor;
	*i++ = blob.outerColor;

	d = (double*)i;
	*d++ = blob.orientation;
	*d++ = blob.velocityRot;
	*d++ = blob.velocityx;
	*d++ = blob.velocityy;

	if (send(simSocket, (char*)&data, sizeof(data), 0) < 0)
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