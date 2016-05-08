#include "bot_socket.h"
#include "stdafx.h"

/** 
 * Refer to the following link for Microsoft's Server C++ code:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms737593(v=vs.85).aspx
 *
 */

#define DEFAULT_BUFFER_SIZE 512

const char * MinibotServer::IPADDRESS = "127.0.0.1";
const int MinibotServer::PORT = 607;

WSADATA MinibotServer::wsa;
SOCKET MinibotServer::botSocket;
struct sockaddr_in MinibotServer::botAddr;

int MinibotServer::setupBotSocket()
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

	if (bind(botSocket, (SOCKADDR *)&botAddr, sizeof(botAddr)) == SOCKET_ERROR)
	{
		printf("Connection error :: binding.\n");
		closeBotSocket();
		return -1;
	}
	else
	{
		printf("Connected.\n");
	}

	return 0;
}


int MinibotServer::server() {
	char buff[DEFAULT_BUFFER_SIZE];
	int buff_len = DEFAULT_BUFFER_SIZE;
	int bytes_rec = 0;


	printf("Waiting to receive from Simulation...\n");
	do {
		if ((bytes_rec = recv(botSocket, buff, buff_len, 0)) > 0) {
			printf("Bytes received %d\n", bytes_rec);
			printf("Data received\n %s", buff);
		}
		else if (bytes_rec == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed with error: %d", WSAGetLastError());
			closesocket(botSocket);
		}
	} while (bytes_rec > 0);

	if (shutdown(botSocket, SD_SEND) == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError);
		closesocket(botSocket);
		WSACleanup();
		return -1;
	}

	closesocket(botSocket);
	WSACleanup();

	return 0;
}



int MinibotServer::closeBotSocket()
{
	closesocket(botSocket);
	WSACleanup();

	return 0;
}

int MinibotServer::sendMotorControl(Control *pkt)
{
	char data[68];
	int *i;
	float *f;

	i = (int *)data;
	*i++ = pkt->orientation;
	*i++ = pkt->direction;

	f = (float *)i;
	*f++ = pkt->velocity;


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
