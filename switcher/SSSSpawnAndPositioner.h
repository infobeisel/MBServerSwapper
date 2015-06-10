#ifndef SSSSPAWNANDPOSITIONER_H
#define SSSSPAWNANDPOSITIONER_H
#include "SSState.h"

class SSSSpawnAndPositioner : public SSState
{
    public:
        SSSSpawnAndPositioner();
        virtual ~SSSSpawnAndPositioner();
    void process() ;
    void entry() ;
    protected:
    SSState* next();
    private:

};

#endif // SSSSPAWNANDPOSITIONER_H
