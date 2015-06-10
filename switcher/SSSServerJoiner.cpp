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

}

SSState* SSSServerJoiner::next()
{
    SSState* ret = this;
    if(GameValueProvider::get()->isJoinedServer())
    {
        SSSSpawnAndPositioner* newState = new SSSSpawnAndPositioner();
        //copy values
        newState->setCurLocation(this->curLocation);
        newState->setWishedTravelDir(this->wishedTravelDir);
        ret = newState;
    }
    return ret;
}
