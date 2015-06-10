#include "SSState.h"

SSState::SSState()
{
    curLocation = std::string();
    wishedTravelDir = -1;
}

SSState::~SSState()
{
    //dtor
}




SSState* SSState::getNext(){
    SSState* newState = next();
    // do we have a new State?
    if(this != newState) {
		this->exit();
        newState->entry();
        return newState;
    } else {
        return this;
    }
}

void SSState::setCurLocation(std::string loc){this->curLocation = loc;};
void SSState::setWishedTravelDir(int dir){this->wishedTravelDir = dir;};

