#include "SSState.h"

SSState::SSState()
{
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


