#ifndef SSSSERVERFINDER_H
#define SSSSERVERFINDER_H
#include "SSState.h"
#include "ServerGraph.h"

class SSSServerFinder : public SSState
{
    public:
        SSSServerFinder();
        virtual ~SSSServerFinder();
        void process() ;
        void entry() ;
   protected:
           SSState* next();

    private:
        bool serverFound = false;
        ServerGraph* graph;
};

#endif // SSSSERVERFINDER_H
