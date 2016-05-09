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
#define SOCKET_READ_TIMEOUT_SEC 1


const char * MinibotServer::IPADDRESS = "192.168.4.12";
const int MinibotServer::PORT = 607;

int MinibotServer::botSocket;
struct sockaddr_in MinibotServer::botAddr;

volatile int direction = DIRECTION_STOP;
volatile int drive_time = 0;
volatile int drive_RPM = 0;

using namespace Servo;



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

	fd_set set;
	struct timeval timeout;
	timeout.tv_sec = SOCKET_READ_TIMEOUT_SEC;
	timeout.tv_usec = 0;

	do {
		printf("Waiting to receive from Simulation...\n");
		FD_ZERO(&set); /* clear the set */
		FD_SET(botSocket, &set); /* add our file descriptor to the set */
		int rv = select(botSocket+1, &set, NULL, NULL, &timeout);
		if (rv <= 0)
		{
		    // timeout, socket does not have anything to read
		    printf("Have no data to receive. \n");
		    drive_motors(0.0f, DIRECTION_STOP);
		    continue;
		}
		if ((bytes_rec = recv(botSocket, buff, buff_len, 0)) > 0) {
			printf("Bytes received %d\n", bytes_rec);
			printf("Data received\n %s", buff);

			Control pkt;
			int *i = (int *)buff;
			pkt.orientation = *i++;
			pkt.direction = *i++;

			float *f = (float *)i;
			pkt.velocity = (*f++); // scale from m/sec  to m/min

			direction = DIRECTION_STOP;
			printf("Int Vel: %f\n", pkt.velocity);
			if (((int) pkt.velocity)> 0) {
			printf("We are moving!! :D\n");
			if (pkt.direction == 1) {
				direction = DIRECTION_FORWARD;
			} else if (pkt.direction == 0) {
				direction = DIRECTION_BACKWARD;
			}
			}

			pkt.velocity += 14;
			printf("command %d %f\n", pkt.direction, pkt.velocity);
			

			drive_motors(pkt.velocity, direction);		
		}
		else if (bytes_rec == 0) {
			printf("Connection closing...\n");
		}
		else {
			printf("recv failed\n"); 
			close(botSocket);
		}
	} while (bytes_rec >= 0);

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
