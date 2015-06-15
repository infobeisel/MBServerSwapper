#include "GameValueProvider.h"
#include <Windows.h>
#include "Defines.h"
#include <iostream>

GameValueProvider* GameValueProvider::instance = 0;

GameValueProvider* GameValueProvider::get()
{
  if( instance == 0 )
    instance = new GameValueProvider();
  return instance;
}
GameValueProvider::~GameValueProvider()
{
    //dtor
}

void GameValueProvider::setProcessHandle(HANDLE hnd) {
    this->gameProcess = hnd;
}
void GameValueProvider::setProcessMainWindow(HWND hnd) {
    this->gameMainWindow = hnd;
}
void GameValueProvider::setProcessBaseAdress(DWORD adr) {
    this->gameBaseAdress = adr;
}


HWND* GameValueProvider::getProcessMainWindow( ) {
    return &gameMainWindow;
}

bool GameValueProvider::isGameInForeground() {
    HWND h = GetForegroundWindow();
    return (h==gameMainWindow);
}
//deprecated  bool GameValueProvider::isInMainMenu() {}
bool GameValueProvider::isClosed() {
    DWORD status;
    GetExitCodeProcess(gameProcess,&status);
    return status!=STILL_ACTIVE;
}
int* GameValueProvider::getResolution() {
    //first two vals ingame effective width, heigth, then window width, height, then positions as returned by GetWindowRect
    int res[] = {0,0,0,0,0,0,0,0};

    //window
    HWND found = NULL;
    found = gameMainWindow;//FindWindowW(NULL,GAME_NAME);
    RECT rec;
    GetWindowRect(found,&rec);

    //ingame resolution
    int x = 0;
    DWORD addr = (gameBaseAdress + WINDOW_EFFECTIVE_SIZE_X_OFFSET);
    ReadProcessMemory(gameProcess,(void*)addr,&x,sizeof(x) ,NULL);
    int y = 0;
    addr = (gameBaseAdress + WINDOW_EFFECTIVE_SIZE_Y_OFFSET);
    ReadProcessMemory(gameProcess,(void*)addr,&y,sizeof(y) ,NULL);
    res[0] = x;
    res[1] = y;
    res[2] = rec.right - rec.left;
    res[3] = rec.bottom - rec.top;
    res[4] = rec.bottom;
    res[5] = rec.left;
    res[6] = rec.right;
    res[7] = rec.top;
    return res;
}

std::string GameValueProvider::getCurrentChosenMapName() {
    SIZE_T  lpNumberOfBytesRead;
    char retCharArr[MAP_NAME_LENGTH_CONVENTION + 1] = {};
    DWORD addr= (gameBaseAdress + MAP_NAME_ADDR_OFFSET);
    ReadProcessMemory(gameProcess,(void*)addr,&retCharArr,MAP_NAME_LENGTH_CONVENTION ,&lpNumberOfBytesRead);
    //terminate symbol.no.
    retCharArr[MAP_NAME_LENGTH_CONVENTION ] = 0;
    std::string ret = std::string(retCharArr);
    return ret;
}
int GameValueProvider::getCurrentChosenServerListIndex() {
    DWORD addr = dereferencePointer(SERVER_LIST_INFO_CUR_SEL_INDEX_POINTER_OFFSET,
                                    SERVER_LIST_INFO_CUR_SEL_INDEX_OFFSETS);
    int res = 0;
    ReadProcessMemory(gameProcess,(void*)addr,&res,sizeof(res) ,NULL);
    return res;
}

void GameValueProvider::setCurrentChosenServerListIndex(int i) {
    DWORD addr = dereferencePointer(SERVER_LIST_INFO_CUR_SEL_INDEX_POINTER_OFFSET,
                                    SERVER_LIST_INFO_CUR_SEL_INDEX_OFFSETS);
    DWORD res = (DWORD) i;
    WriteProcessMemory(gameProcess,(void*)addr,&res,sizeof(res) ,NULL);
}

std::string GameValueProvider::getCurrentChosenIp() {
	//length of selected ip
	DWORD addr = dereferencePointer(SERVER_INFO_IP_LENGTH_POINTER_OFFSET,
		SERVER_INFO_IP_LENGTH_OFFSETS);
	int length = 1;
	ReadProcessMemory(gameProcess, (void*)addr, &length, sizeof(length), NULL);
	addr = dereferencePointer(SERVER_INFO_IP_POINTER_OFFSET,
		SERVER_INFO_IP_OFFSETS);
	char res[100];
	res[length] = '\0';
	ReadProcessMemory(gameProcess, (void*)addr, &res, length, NULL);
	std::string req(res);
	return req;
}
int GameValueProvider::getCurrentChosenPort() {
	//port pointer
	int result;
	DWORD addr = dereferencePointer(SERVER_INFO_PORT_POINTER_OFFSET,
		SERVER_INFO_PORT_OFFSETS);
	ReadProcessMemory(gameProcess, (void*)addr, &result, sizeof(result), NULL);
	return result;


}



//deprecated
/*
bool GameValueProvider::isInServerListScreen() {
    DWORD addr = (gameBaseAdress + SERVER_LIST_INFO_IS_IN_SERVER_LIST_OFFSET);
    int res = 0;
    ReadProcessMemory(gameProcess,(void*)addr,&res,sizeof(res) ,NULL);
    return (res == SERVER_LIST_INFO_IS_IN_SERVER_LIST_TRUE_VAL) ? true : false;
}*/
bool GameValueProvider::isInCharScreen() {
    char charScreen[CHAR_SCREEN_REACHED_EVENT_STRING_LENGTH + 1] = {};
    DWORD addr= (gameBaseAdress + CHAR_SCREEN_REACHED_EVENT_ADDR_OFFSET);
    ReadProcessMemory(gameProcess,(void*)addr,&charScreen,CHAR_SCREEN_REACHED_EVENT_STRING_LENGTH ,NULL);
    //terminate symbol
    charScreen[CHAR_SCREEN_REACHED_EVENT_STRING_LENGTH] = 0;
    std::string screenmessage = std::string(charScreen);
    std::string shouldbe = std::string(CHAR_SCREEN_REACHED_EVENT_MESSAGE);
    std::cout << screenmessage << " should be    " << shouldbe  << "\n";

   int ret = false;
    if     ((screenmessage.compare(shouldbe)) == 0) ret = true;
    return ret;
}

void GameValueProvider::flushInCharScreenMessage() {
    char charScreen[CHAR_SCREEN_REACHED_EVENT_STRING_LENGTH ] = {0};
    DWORD addr= (gameBaseAdress + CHAR_SCREEN_REACHED_EVENT_ADDR_OFFSET);
    WriteProcessMemory(gameProcess,(void*)addr,&charScreen,CHAR_SCREEN_REACHED_EVENT_STRING_LENGTH ,NULL);
}

bool GameValueProvider::isJoinedServer() {
    char joinedMessage[SERVER_JOINED_EVENT_STRING_LENGTH + 1] = {};
    DWORD addr= (gameBaseAdress + SERVER_JOINED_EVENT_ADDR_OFFSET);
    ReadProcessMemory(gameProcess,(void*)addr,&joinedMessage,SERVER_JOINED_EVENT_STRING_LENGTH ,NULL);
    //terminate symbol
    joinedMessage[SERVER_JOINED_EVENT_STRING_LENGTH] = 0;
    std::string screenmessage = std::string(joinedMessage);
    std::string shouldbe = std::string(SERVER_JOINED_EVENT_MESSAGE);
    int ret = false;
    if     ((screenmessage.compare(shouldbe)) == 0) ret = true;
    return ret;
}
void GameValueProvider::flushIsJoinedServerMessage() {
    char joinedMessage[SERVER_JOINED_EVENT_STRING_LENGTH ] = {0};
    DWORD addr= (gameBaseAdress + SERVER_JOINED_EVENT_ADDR_OFFSET);
    WriteProcessMemory(gameProcess,(void*)addr,&joinedMessage,SERVER_JOINED_EVENT_STRING_LENGTH ,NULL);
}
bool GameValueProvider::isFilterPanelOpen() {
    DWORD addr = dereferencePointer(FILTER_PANEL_POINTER_OFFSET,FILTER_PANEL_ACTIVE_CHECKED_OFFSETS);
    bool ret = (getIntValue(addr) == 1) ? true : false;
    return ret;
}

bool GameValueProvider::isHasPlayersFilterChecked() {
    DWORD addr = dereferencePointer(FILTER_PANEL_POINTER_OFFSET,FILTER_PANEL_HAS_PLAYERS_CHECKED_OFFSETS);
    bool ret = (getIntValue(addr) == 1) ? true : false;
    return ret;
}

bool GameValueProvider::isPasswordFreeChecked() {
    DWORD addr = dereferencePointer(FILTER_PANEL_POINTER_OFFSET,FILTER_PANEL_IS_PASSWORD_FREE_CHECKED_OFFSETS);
    bool ret = (getIntValue(addr) == 1) ? true : false;
    return ret;
}
bool GameValueProvider::isVersionCompatibleChecked() {
    DWORD addr = dereferencePointer(FILTER_PANEL_POINTER_OFFSET,FILTER_PANEL_IS_VERSION_COMPATIBLE_CHECKED_OFFSETS);
    bool ret = (getIntValue(addr) == 1) ? true : false;
    return ret;
}


int GameValueProvider::getMatchModeFilterIndex() {
    DWORD addr = dereferencePointer(FILTER_PANEL_POINTER_OFFSET,FILTER_PANEL_MATCH_MODE_INDEX_OFFSETS);
   return (getIntValue(addr));
}

int GameValueProvider::getPingLimitFilterIndex() {
    DWORD addr = dereferencePointer(FILTER_PANEL_POINTER_OFFSET,FILTER_PANEL_PING_LIMIT_INDEX_OFFSETS);
   return (getIntValue(addr));
}


int GameValueProvider::getTravelDirection() {
    SIZE_T  lpNumberOfBytesRead;
    char travelReq[TRAVEL_REQUEST_STRING_LENGTH + 1] = {};
    DWORD addr= (gameBaseAdress + TRAVEL_REQUEST_ADDR_OFFSET);
    ReadProcessMemory(gameProcess,(void*)addr,&travelReq,TRAVEL_REQUEST_STRING_LENGTH ,&lpNumberOfBytesRead);
    //terminate symbol.no.
    travelReq[TRAVEL_REQUEST_STRING_LENGTH ] = 0;
    std::string req = std::string(travelReq);
    int ret = -1;
    if     (req.compare(std::string(TRAVEL_REQUEST_NORTH)) == 0) ret = TRAVEL_DIR_NORTH;
    else if(req.compare(std::string(TRAVEL_REQUEST_EAST)) == 0) ret = TRAVEL_DIR_EAST;
    else if(req.compare(std::string(TRAVEL_REQUEST_SOUTH)) == 0) ret = TRAVEL_DIR_SOUTH;
    else if(req.compare(std::string(TRAVEL_REQUEST_WEST)) == 0) ret = TRAVEL_DIR_WEST;

    return ret;
}
void GameValueProvider::flushTravelDirectionMessage() {
   char travelReq[TRAVEL_REQUEST_STRING_LENGTH ] = {0};
    DWORD addr= (gameBaseAdress + TRAVEL_REQUEST_ADDR_OFFSET);
    WriteProcessMemory(gameProcess,(void*)addr,&travelReq,TRAVEL_REQUEST_STRING_LENGTH ,NULL);
}

HWND GameValueProvider::getGameMainWindow() {return gameMainWindow;}


/** returns absolute address**/
DWORD GameValueProvider::dereferencePointer(DWORD baseToPointerOffset,std::vector<DWORD> pointerToValuesOffsets){
    DWORD pointerAdress = gameBaseAdress + baseToPointerOffset;
    DWORD addressContent;
    ReadProcessMemory(gameProcess,(void*)pointerAdress,&addressContent,sizeof(addressContent) ,NULL);
    for(DWORD off :  pointerToValuesOffsets) {
        pointerAdress = addressContent + off;
        ReadProcessMemory(gameProcess,(void*)pointerAdress,&addressContent,sizeof(addressContent) ,NULL);
    }
    return pointerAdress;
}
/** takes absolute address **/
int GameValueProvider::getIntValue(DWORD atAbsAddr) {
    DWORD addr = atAbsAddr;
    int res = 0;
    ReadProcessMemory(gameProcess,(void*)addr,&res,sizeof(res) ,NULL);
    return res;
}


