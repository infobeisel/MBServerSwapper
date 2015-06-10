#ifndef SSSIDLE_H
#define SSSIDLE_H

#include "SSState.h"

class SSSIdle : public SSState {
    public:
        SSSIdle();
        virtual ~SSSIdle();

    void process() ;
    void entry() ;
	void exit();
    protected:
    SSState* next();
    private:
        bool wantsSwitch;
};

#endif // SSSIDLE_H
