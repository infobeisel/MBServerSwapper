#include "SSSServerJoiner.h"
#include "IOHandler.h"
#include "GameValueProvider.h"
#include "SSSSpawnAndPositioner.h"
SSSServerJoiner::SSSServerJoiner()
{
    //ctor
}

SSSServerJoiner::~SSSServerJoiner()
{
    //dtor
}

void SSSServerJoiner::process() {
	//TODO type in password
    //click on join
    IOHandler* hnd = IOHandler::get();
    hnd->setCursorPos(BUTTON_JOIN_SERVER_X,BUTTON_JOIN_SERVER_Y);
    Sleep(5);
    hnd->fireMouseClick(MOUSE_LEFT_CLICK);
    Sleep(CLICK_WAIT_TIME);
}
void SSSServerJoiner::entry() {
    std::cout<< "Server found! Joining server..." << "\n";
    //flush event messages to get new ones later
    GameValueProvider* g = GameValueProvider::get();
    g->flushIsJoinedServerMessage();
    g->flushInCharScreenMessage();
    g->flushTravelDirectionMessage();

}
void SSSServerJoiner::exit() {
	IOHandler::get()->stopLoadingAnimation(GameValueProvider::get()->getGameMainWindow());
	//unblock mouse input
	int ret = BlockInput(false);//block mouse input

}

SSState* SSSServerJoiner::next()
{
    SSState* ret = this;
    if(GameValueProvider::get()->isJoinedServer())
    {
        SSSSpawnAndPositioner* newState = new SSSSpawnAndPositioner();
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
