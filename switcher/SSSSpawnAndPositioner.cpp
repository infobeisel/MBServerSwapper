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
    return newState;

}

void SSSSpawnAndPositioner::entry(){
    std::cout << "jump to Idle" << "\n";
}

void SSSSpawnAndPositioner::process() {
    return;
}

