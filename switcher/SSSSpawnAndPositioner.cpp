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
	newState->ip = "";
	newState->iplength = 0;
	newState->password = "";
	newState->port = 0;
	newState->passwordlength = 0;
	return newState;

}

void SSSSpawnAndPositioner::entry(){
    std::cout << "jump to Idle" << "\n";
}

void SSSSpawnAndPositioner::process() {
    return;
}

