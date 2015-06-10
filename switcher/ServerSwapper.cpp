#include "ServerSwapper.h"
#include "SSSServerFinder.h"
#include "SSSIdle.h"
#include "SSSServerListNavigator.h"

ServerSwapper::ServerSwapper()
{
    state = new SSSIdle();
    state->entry();

}

ServerSwapper::~ServerSwapper()
{
    //dtor
}

void ServerSwapper::run() {
    //let the state do his stuff
    state->process();
    //do we need a new state?
    state = (state->getNext());
}



void ServerSwapper::setState(SSState* pState) {
    this->state = pState;
}

void ServerSwapper::setWishedTravelDir(int dir) {this->wishedTravelDir = dir;}
int ServerSwapper::getWishedTravelDir() {return this->wishedTravelDir;}
void ServerSwapper::setCurLocation(std::string loc) {this->curLocation = loc;}
std::string ServerSwapper::getCurLocation() {return this->curLocation;}
