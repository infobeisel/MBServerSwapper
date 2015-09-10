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
    //int t = GameValueProvider::get()->getTravelDirection();
	 bool t = GameValueProvider::get()->wantsTravel();
  if(t) {
      //next() will give another state than this
        this->wantsSwitch = true;
        //store data
		this->iplength = GameValueProvider::get()->getRegAsInt(0);
		this->port = GameValueProvider::get()->getRegAsInt(1);
		this->passwordlength = GameValueProvider::get()->getRegAsInt(2);
		this->ip = GameValueProvider::get()->getStringReg(20, this->iplength);
		this->password = GameValueProvider::get()->getStringReg(1, this->passwordlength);

		std::cout << "now search after " << this->ip << "with length" << this->iplength << "and port" << this->port<< "\n";

        //this->wishedTravelDir = t;
        //this->curIp = GameValueProvider::get()->getCurrentChosenIp();
		//this->curLocation = GameValueProvider::get()->getCurrentChosenMapName();

    }
 }
 void SSSIdle::entry() {
    std::cout << "wait for server-swap-request" << "\n";
    //flushing after waiting a short time
    Sleep(CLICK_WAIT_TIME);
    GameValueProvider::get()->flushInCharScreenMessage();
    GameValueProvider::get()->flushIsJoinedServerMessage();
    GameValueProvider::get()->flushTravelDirectionMessage();
	
	ShowCursor(TRUE);



}
 void SSSIdle::exit() {
	 IOHandler::get()->startLoadingAnimation(GameValueProvider::get()->getGameMainWindow()); //start loading screen
	 BlockInput(true);//block mouse input



 }


 SSState* SSSIdle::next() {
      SSState* ret = this;
    if(this->wantsSwitch) {
        SSSServerListNavigator* newState = new SSSServerListNavigator();
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
