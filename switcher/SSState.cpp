#include "SSState.h"

SSState::SSState()
{
	this->ip = std::string();
	this->iplength = 0;
	this->password = std::string();
	this->port = 0;
	this->passwordlength = 0;
}

SSState::~SSState()
{
	ip.clear();
	password.clear();

}




SSState* SSState::getNext(){
    SSState* newState = next();
    // do we have a new State?
    if(this != newState) {
		this->exit();
        newState->entry();
		this->~SSState();
        return newState;
    } else {
        return this;
    }
}


