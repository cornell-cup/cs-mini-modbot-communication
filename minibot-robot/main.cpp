#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{ 

	int result = MinibotServer::setupBotSocket();
	if (result < 0) printf("FAILED TO SETUP SIM SOCKET!\n");

	result = MinibotServer::server();
	if (result < 0) printf("FAILED TO START SERVER!\n");

	Sleep(5000);

	return 0;
}

