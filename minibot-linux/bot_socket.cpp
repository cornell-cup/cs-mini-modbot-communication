#include "bot_socket.h"
#include "stdafx.h"

/** 
 * Refer to the following link for Microsoft's Server C++ code:
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms737593(v=vs.85).aspx
 *
 */

#define DEFAULT_BUFFER_SIZE 512
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

const char * MinibotServer::IPADDRESS = "192.168.4.12";
const int MinibotServer::PORT = 607;

int MinibotServer::botSocket;
struct sockaddr_in MinibotServer::botAddr;

int MinibotServer::setupBotSocket()
{

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

	if (bind(botSocket, (struct sockaddr *)&botAddr, sizeof(botAddr)) == SOCKET_ERROR)
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

			Control pkt;
			int *i = (int *)buff;
			pkt.orientation = *i++;
			pkt.direction = *i++;

			float *f = (float *)i;
			pkt.velocity = (*f++) / 125 + 14; // scale from m/sec  to m/min

			direction = DIRECTION_STOP;
			if (((int) pkt.velocity) - 14 > 0) {
			if (pkt.orientation == 1) {
				direction = DIRECTION_FORWARD;
			} else if (pkt.orientation == 0) {
				direction = DIRECTION_BACKWARD;
			}
			}

			
			drive_motors(0, direction);


			printf("command %c %d %f\n", dir, time, pkt.velocity);


			char command[20] = "./motorcontrol ";
			command[15] = dir;
			command[16] = ' ';
			command[17] = '1';
			command[18] = ' ';
			command[19] = '\0';
			char speed[10];
			sprintf(speed, "%.4f", pkt.velocity);
			strcat(command, speed);

			printf("%s\n", command);
			system(command);

			direction

			

		}
		else if (bytes_rec == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed\n"); 
			close(botSocket);
		}
	} while (bytes_rec > 0);

	close(botSocket);

	return 0;
}



int MinibotServer::closeBotSocket()
{
	close(botSocket);

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
