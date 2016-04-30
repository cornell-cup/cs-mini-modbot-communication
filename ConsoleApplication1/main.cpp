#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FakeBlob blob;
	blob.id = 2;
	blob.time = 2.643;
	blob.x = 2.1334;
	blob.y = 4.7655;
	blob.innerColor = 1;
	blob.outerColor = 2;
	blob.orientation = 2.6342;
	blob.velocityRot = 4.3647;
	blob.velocityx = 6.375345;
	blob.velocityy = 2.36347;

	int result = SimulationClient::setupSimSocket();
	if (result < 0) printf("FAILED TO SETUP SIM SOCKET!\n");

	result = SimulationClient::sendVisionBlob(blob);
	if (result < 0) printf("FAILED TO SEND BLOB DATA!\n");

	result = SimulationClient::closeSimSocket();
	if (result < 0) printf("FAILED TO CLOSE SIM SOCKET!\n");

	Sleep(5000);

	return 0;
}

