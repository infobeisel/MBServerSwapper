// switcher.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "SocketManager.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SocketManager mng = SocketManager();
	mng.init();
	mng.run();

	return 0;
}

