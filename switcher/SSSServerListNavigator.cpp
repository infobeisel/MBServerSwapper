#include "SSSServerListNavigator.h"
#include "IOHandler.h"
#include "GameValueProvider.h"
#include "SSSServerFinder.h"
SSSServerListNavigator::SSSServerListNavigator()
{
    isInServerList = false;
}

SSSServerListNavigator::~SSSServerListNavigator()
{
    //dtor
}

void SSSServerListNavigator::entry(){

    std::cout << "go to server list..." << "\n";
	//start the loading animation
	//IOHandler::get()->startLoadingAnimation(GameValueProvider::get()->getGameMainWindow());


}
void SSSServerListNavigator::process(){


            GameValueProvider* g = GameValueProvider::get();

            //until character menu isn't reached...
            if(!g->isInCharScreen()) return;
            Sleep(CLICK_WAIT_TIME);
            //flush in char screen message, wait for new one
            GameValueProvider::get()->flushInCharScreenMessage();

            IOHandler* hnd = IOHandler::get();
            Sleep(CLICK_WAIT_TIME);

            //click on "ok" (message box: kicked by server)
            hnd->setCursorPos(BUTTON_KICKED_OK_X,BUTTON_KICKED_OK_Y);
            hnd->fireMouseClick(0);
            Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            //click on "entry server"
            hnd->setCursorPos(BUTTON_JOIN_SERVER_LIST_X,BUTTON_JOIN_SERVER_LIST_Y);
            hnd->fireMouseClick(0);
            Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            //click on network dropdown menu
            hnd->setCursorPos(BUTTON_DROP_DOWN_NETWORK_X,BUTTON_DROP_DOWN_NETWORK_Y);
           hnd->fireMouseClick(0);
            Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            //click on Internet
            hnd->setCursorPos(BUTTON_DROP_DOWN_NETWORK_INTERNET_X,BUTTON_DROP_DOWN_NETWORK_INTERNET_Y);
            hnd->fireMouseClick(0);
            Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            //click on filter panel
            if(!g->isFilterPanelOpen()) {
                hnd->setCursorPos(BUTTON_FILTER_PANEL_X,BUTTON_FILTER_PANEL_Y);
                hnd->fireMouseClick(0);
                Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            }
            if(g->isHasPlayersFilterChecked()) {
                hnd->setCursorPos(BUTTON_FILTER_HAS_PLAYERS_X,BUTTON_FILTER_HAS_PLAYERS_Y);
                hnd->fireMouseClick(0);
                Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            }
            //uncheck everything except is version compatible TODO
            if(!g->isVersionCompatibleChecked()) {
                hnd->setCursorPos(BUTTON_FILTER_IS_VERSION_COMPATIBLE_X,BUTTON_FILTER_IS_VERSION_COMPATIBLE_Y);
                hnd->fireMouseClick(0);
                Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            }
            if(g->isPasswordFreeChecked()) {
                hnd->setCursorPos(BUTTON_FILTER_IS_PASSWORD_FREE_X,BUTTON_FILTER_IS_PASSWORD_FREE_Y);
                hnd->fireMouseClick(0);
                Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            }
            while(g->getMatchModeFilterIndex() != 0) {
                hnd->setCursorPos(BUTTON_FILTER_MATCH_MODE_PREV_X,BUTTON_FILTER_MATCH_MODE_PREV_Y);
                hnd->fireMouseClick(0);
                Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            }
            while(g->getPingLimitFilterIndex() != 0) {
                hnd->setCursorPos(BUTTON_FILTER_PING_LIMIT_PREV_X,BUTTON_FILTER_PING_LIMIT_PREV_Y);
                hnd->fireMouseClick(0);
                Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
            }
            //we got here? ok, finish state
            isInServerList = true;

}
SSState* SSSServerListNavigator::next(){
    SSState* ret = this;
    if(isInServerList) {
        SSSServerFinder* newState = new SSSServerFinder();
         //copy values
		newState->ip = (this->ip);
		newState->iplength = (this->iplength);
		newState->password = (this->password);
		newState->port = (this->port);
		newState->passwordlength = (this->passwordlength);
        ret = newState;
    }
    return ret;
}
