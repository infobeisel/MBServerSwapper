#include "SSSIdle.h"
#include "Defines.h"
#include "GameValueProvider.h"
#include "SSSServerListNavigator.h"
#include <iostream>
#include "IOHandler.h"
SSSIdle::SSSIdle()
{
    this->wantsSwitch = false;
}

SSSIdle::~SSSIdle()
{
    //dtor
}


 void SSSIdle::process() {
    int t = GameValueProvider::get()->getTravelDirection();

  if(t != TRAVEL_DIR_NOOP) {
      //next() will give another state than this
        this->wantsSwitch = true;
        //store data
        this->wishedTravelDir = t;
        //this->curIp = GameValueProvider::get()->getCurrentChosenIp();

        this->curLocation = GameValueProvider::get()->getCurrentChosenMapName();

    }
 }
 void SSSIdle::entry() {
    std::cout << "wait for switch-server-command" << "\n";
    //flushing after waiting a short time
    Sleep(CLICK_WAIT_TIME);
    GameValueProvider::get()->flushInCharScreenMessage();
    GameValueProvider::get()->flushIsJoinedServerMessage();
    GameValueProvider::get()->flushTravelDirectionMessage();


}
 void SSSIdle::exit() {
	 IOHandler::get()->startLoadingAnimation(GameValueProvider::get()->getGameMainWindow());

 }


 SSState* SSSIdle::next() {
      SSState* ret = this;
    if(this->wantsSwitch) {
        SSSServerListNavigator* newState = new SSSServerListNavigator();
        //copy values
        newState->setCurLocation(this->curLocation);
        newState->setWishedTravelDir(this->wishedTravelDir);
        ret = newState;
    }
    return ret;
 }
