#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include "GameValueProvider.h"
#include "ServerSwapper.h"
#include "IOHandler.h"

#include <TlHelp32.h>

class SocketManager
{
    public:
        SocketManager();
        virtual ~SocketManager();

        void init();
        void run();
    protected:
    private:
        GameValueProvider* gameValues;
        ServerSwapper* swapper;


        /** copypaste (https://msdn.microsoft.com/en-us/library/windows/desktop/ms686849%28v=vs.85%29.aspx)
        and light modification to get base adress of game process**/
        DWORD getBaseAdress( DWORD dwPID );



};

#endif // SOCKETMANAGER_H
