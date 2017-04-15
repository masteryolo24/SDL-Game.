#include "stdafx.h"
#include "Main.h"

int main(int argc, char *argv[])
{
	CMain* cmain = new CMain(1366, 700);
	cmain->OnExecute();

	delete cmain;
	return 0;
}