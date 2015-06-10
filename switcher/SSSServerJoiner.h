#ifndef SSSSERVERJOINER_H
#define SSSSERVERJOINER_H
#include "SSState.h"

class SSSServerJoiner : public SSState
{
    public:
        SSSServerJoiner();
        virtual ~SSSServerJoiner();

        void process() ;
        void entry() ;
		void exit();
    protected:

    private:
        SSState* next();
};

#endif // SSSSERVERJOINER_H
