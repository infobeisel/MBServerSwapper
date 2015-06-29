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

	//target ip
	std::string ip;
	//target ip length
	int iplength;
	//target port
	int port;
	//target password
	std::string password;
	///target password length;
	int passwordlength;

protected:

	



    /**evaluates the next state. could be this**/
    virtual SSState* next()
    {
        return this;
    };


private:

};

#endif // SSSTATE_H
