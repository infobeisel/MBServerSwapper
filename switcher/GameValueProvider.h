#ifndef GAMEVALUEPROVIDER_H
#define GAMEVALUEPROVIDER_H



#include <Windows.h>
#include "Defines.h"
class GameValueProvider
{
    public:
         GameValueProvider() {}
        static GameValueProvider* get();
        virtual ~GameValueProvider();
        std::string getCurrentChosenIp();
        int getCurrentChosenServerListIndex();
        void setCurrentChosenServerListIndex(int i);

        std::string getCurrentChosenMapName();


        /** filter panel in server list **/
        bool isFilterPanelOpen();
        bool isHasPlayersFilterChecked();
        bool isVersionCompatibleChecked();
        bool isPasswordFreeChecked();
        int getMatchModeFilterIndex();
        int getPingLimitFilterIndex();

        /** returns direction, the player wants to travel.**/
        int getTravelDirection();
        void flushTravelDirectionMessage();
        /** events (means they return only temporarily true although the semantic statement stays true)**/
        // deprecated bool isInServerListScreen();
        bool isInCharScreen();
        void flushInCharScreenMessage();
        //deprecated bool isInMainMenu();
        bool isJoinedServer();
        void flushIsJoinedServerMessage();

        bool isGameInForeground();
        int* getResolution();
        bool isFullScreen();
        bool isClosed();

        void setProcessHandle(HANDLE hnd);
        void setProcessMainWindow(HWND hnd);
        HWND* getProcessMainWindow();
        void setProcessBaseAdress(DWORD adr);

        HWND getGameMainWindow();
    protected:
   private:
        static GameValueProvider* instance;
        HANDLE gameProcess;
        HWND    gameMainWindow;
        DWORD gameBaseAdress;
        /** returns the final address the given pointer + offset array point on **/
        DWORD dereferencePointer(DWORD baseToPointerOffset,std::vector<DWORD> pointerToValuesOffsets);
        /** returns int value at given address **/
        int getIntValue(DWORD atAddr);
        /** returns string value at given address **/
        std::string getStringValue(DWORD atAddr,int lenth);






};


#endif // GAMEVALUEPROVIDER_H
