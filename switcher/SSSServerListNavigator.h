#ifndef SSSSERVERLISTNAVIGATOR_H
#define SSSSERVERLISTNAVIGATOR_H
#include "SSState.h"

class SSSServerListNavigator : public SSState
{
    public:
        SSSServerListNavigator();
        virtual ~SSSServerListNavigator();
        void process() ;
        void entry() ;
    protected:
        SSState* next();
        bool isInServerList;
    private:
};

#endif // SSSSERVERLISTNAVIGATOR_H
