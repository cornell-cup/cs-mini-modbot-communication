#include "stdafx.h"

int main(int argc, char* argv[])
{ 

	int result = MinibotServer::setupBotSocket();
	if (result < 0) printf("FAILED TO SETUP SIM SOCKET!\n");

	result = MinibotServer::server();
	if (result < 0) printf("FAILED TO START SERVER!\n");

	sleep(5000);

	return 0;
}

