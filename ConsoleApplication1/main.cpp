// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsa;
	SOCKET serverSocket;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	if ((serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		printf("Could not create socket.\n");
	}
	else
	{
		printf("Socket created.\n");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(607);

	//if (connect(serverSocket, (SOCKADDR *)&server, sizeof(server)) == SOCKET_ERROR)
	if (bind(serverSocket, (SOCKADDR *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Connection error.\n");
	}
	else
	{
		printf("Connected.\n");
	}

	/*
	int data [] = { 42, 63, 23, 75 };
	if (send(serverSocket, (char *)&data, sizeof(data), 0) < 0)
	{
		printf("Send failed.\n");
	}
	else
	{
		printf("Sent.\n");
	}

	shutdown(serverSocket, SD_SEND);
	*/

	char recvBuf[4];
	sockaddr_in senderaddr;
	int senderaddrsize = sizeof(senderaddr);

	while (true){
		int result = recvfrom(serverSocket, recvBuf, 4, 0, (SOCKADDR *)&senderaddr, &senderaddrsize);
		if (result == SOCKET_ERROR) printf("%ld", WSAGetLastError());

		//printf("Received: %f\n", *(float*)&recvBuf);
		//printf("Received: %d\n", *(int*)&recvBuf);
	}

	closesocket(serverSocket);
	WSACleanup();

	Sleep(5000);
	return 0;
}

