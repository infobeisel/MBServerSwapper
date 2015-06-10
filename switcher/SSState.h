#ifndef SSSTATE_H
#define SSSTATE_H
#include "Defines.h"
#include <iostream>

//forward declaration
class ServerSwapper;


class SSState
{

public:
    SSState();
    virtual ~SSState();


    /** get next state (could be this), call entry()-method, destruct old state  **/
    SSState* getNext();


    /** state's main action method. gets called each frame by parent **/
    virtual void process() {};
    /** entry method which is called each time the state changed **/
    virtual void entry() {};
	virtual void exit() {};
    void setCurLocation(std::string loc);
    void setWishedTravelDir(int dir);
protected:
    /** wished travel direction **/
    int wishedTravelDir;
    /** cur location  **/
    std::string curLocation;



    /**evaluates the next state. could be this**/
    virtual SSState* next()
    {
        return this;
    };


private:

};

#endif // SSSTATE_H
