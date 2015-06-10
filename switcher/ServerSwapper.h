#ifndef SERVERSWAPPER_H
#define SERVERSWAPPER_H
#include "GameValueProvider.h"
#include "SSState.h"

class ServerSwapper
{
    public:
        ServerSwapper();
        virtual ~ServerSwapper();
        void run();
        void setState(SSState* pState);


        void setWishedTravelDir(int dir);
        int getWishedTravelDir();
        void setCurLocation(std::string loc);
        std::string getCurLocation();
    protected:

    private:
        SSState* state;
        int wishedTravelDir;
        std::string curLocation;


};

#endif // SERVERSWAPPER_H
