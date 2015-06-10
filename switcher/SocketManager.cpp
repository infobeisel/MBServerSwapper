#include "SocketManager.h"
#include "ServerGraph.h"
#include <Windows.h>



#include <stdio.h>
#include <stdarg.h>
#include "Uxtheme.h"
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#pragma comment (lib,"Winmm.lib")

SocketManager::SocketManager()
{
    //ctor
}

SocketManager::~SocketManager()
{
    //dtor
}


void SocketManager::init() {
    //wait for game process
    HWND found = FindWindowW(NULL,GAME_NAME);
    std::cout << "Waiting for game to be opened";
    while(found == NULL) {
        found = FindWindowW(NULL,GAME_NAME);
    }
    std::cout << "\n" << "game opened"<< "\n";

    // get the process id out of the window handle
    DWORD processId;
    GetWindowThreadProcessId(found,&processId);
   // std::cout << *processId;
    HANDLE processHndl = OpenProcess(PROCESS_ALL_ACCESS,TRUE,processId);
    //connect windows process with GameValueProvider
    gameValues = GameValueProvider::get();
    gameValues->setProcessHandle(processHndl);
    gameValues->setProcessMainWindow(found);
    DWORD base = getBaseAdress(processId);
    gameValues->setProcessBaseAdress(base);
    //setup the server swapper
    swapper = new ServerSwapper();
	IOHandler::get()->initAnimationWindow(found);
	

}

void SocketManager::run() {
    while(true) {

       if(gameValues->isGameInForeground()) {
        swapper->run();
		
        }
        if(gameValues->isClosed()) {
            std::cout << "closed";
            exit(1);
        }
    }
}



DWORD SocketManager::getBaseAdress( DWORD dwPID ) {
     HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
      MODULEENTRY32 me32;
    //  Take a snapshot of all modules in the specified process.
      hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID );
      if( hModuleSnap == INVALID_HANDLE_VALUE )
      {
        std::cout << "SocketManager::getBaseAdress : ERROR :can't get process' modules snapshot.";
        return (DWORD) -1;
      }

    //  Set the size of the structure before using it.
      me32.dwSize = sizeof( MODULEENTRY32 );

    //  Retrieve information about the first module,
    //  and exit if unsuccessful
      if( !Module32First( hModuleSnap, &me32 ) )
      {
        std::cout << "SocketManager::getBaseAdress : ERROR :can't get first process module.";
        CloseHandle( hModuleSnap );     // Must clean up the snapshot object!
        return (DWORD)-1;
      }
      Module32First( hModuleSnap, &me32 );
      DWORD ret = (DWORD) me32.modBaseAddr ;
      //std::cout <<  ret << "\n";//<< "   " << me32.modBaseAddr << "\n";
    /**don't need, main module is first module (above)**/
    //  Now walk the module list of the process,
    //  and display information about each module

    /*     do
      {
       _tprintf( TEXT("\n\n     MODULE NAME:     %s"),             me32.szModule );
        _tprintf( TEXT("\n     executable     = %s"),             me32.szExePath );
        _tprintf( TEXT("\n     process ID     = 0x%08X"),         me32.th32ProcessID );
        _tprintf( TEXT("\n     ref count (g)  =     0x%04X"),     me32.GlblcntUsage );
        _tprintf( TEXT("\n     ref count (p)  =     0x%04X"),     me32.ProccntUsage );
        _tprintf( TEXT("\n     base address   = 0x%08X"), (DWORD) me32.modBaseAddr );
        _tprintf( TEXT("\n     base size      = %d"),             me32.modBaseSize );
        //std::cout << me32.szModule << "\n";

      } while( Module32Next( hModuleSnap, &me32 ) );
    */

    //  Do not forget to clean up the snapshot object.
      CloseHandle( hModuleSnap );
      return ret;
}

