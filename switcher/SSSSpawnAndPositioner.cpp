#include "SSSSpawnAndPositioner.h"
#include "SSSIdle.h"
SSSSpawnAndPositioner::SSSSpawnAndPositioner()
{
    //ctor
}

SSSSpawnAndPositioner::~SSSSpawnAndPositioner()
{
    //dtor
}

SSState* SSSSpawnAndPositioner::next() {
    //directly return idle
    //TODO
    SSState* newState = new SSSIdle();
	//copy values
	newState->ip = (this->ip);
	newState->iplength = (this->iplength);
	newState->password = (this->password);
	newState->port = (this->port);
	newState->passwordlength = (this->passwordlength);
	return newState;

}

void SSSSpawnAndPositioner::entry(){
    std::cout << "jump to Idle" << "\n";
}

void SSSSpawnAndPositioner::process() {
    return;
}

