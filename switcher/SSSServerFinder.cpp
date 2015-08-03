#include "SSSServerFinder.h"
#include "GameValueProvider.h"
#include "IOHandler.h"
#include "ServerGraph.h"
#include "SSSServerJoiner.h"
SSSServerFinder::SSSServerFinder()
{

}

SSSServerFinder::~SSSServerFinder()
{
    //dtor
}
void SSSServerFinder::entry()
{
	//std::cout << "lookup server in graph..." << "\n";
	//graph = new ServerGraph();
   // graph->setUpGraph(FileParser::get());
	//graph->setUpGraph(FileParser::get());



    std::cout << "search server in list..." << "\n";
    //wait for game to receive server info
    Sleep(SERVER_LIST_INFO_WAIT_TIME);
    //click on refresh to stop server receive
    IOHandler* hnd = IOHandler::get();
    hnd->setCursorPos(BUTTON_REFRESH_SERVER_LIST_X,BUTTON_REFRESH_SERVER_LIST_Y);
    Sleep(5);
	if (GameValueProvider::get()->îsRetrievingServerInfos())
	{
		hnd->fireMouseClick(MOUSE_LEFT_CLICK);
	}
    Sleep(CLICK_WAIT_TIME);
}
void SSSServerFinder::process()
{
    GameValueProvider* g = GameValueProvider::get();
    IOHandler* hnd = IOHandler::get();
    //curLocation contains current Map Name
    //std::cout << "cur location was  " << curLocation << "\n";
    //std::string currentNodeId = graph->getNodeIdFromMapName(this->curLocation);
    //std::cout << "cur evaluated node:  " << currentNodeId << "\n";
    //std::string node = graph->traverseGraph(currentNodeId,this->wishedTravelDir);
    //std::string wantedIp = graph->getIp(node);
	//more than one dedicated servers can run on the same ip, so also check the port!
	//int			wantedPort = graph->getPort(node);
    //until server found
    while (true)
    {
        //watch visible entries on screen
        for(int i = 0; i < (SERVER_LIST_INFO_WATCH_ENTRIES_UNTIL_SCROLLDOWN/2); i++)
        {
            //from top
            hnd->setCursorPos(SERVER_LIST_FIRST_ENTRY_X,SERVER_LIST_FIRST_ENTRY_Y + (i * SERVER_LIST_NEXT_ENTRY_Y));
            Sleep(5);
            hnd->fireMouseClick(MOUSE_LEFT_CLICK);
            Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
			std::cout <<"search |" <<  (this->ip) << "::" << this->port <<"|\n|";
			std::cout << g->getCurrentChosenIp() << "::" << g->getCurrentChosenPort() << "|\n|";
			//if we found it
			if ((this->ip).compare(g->getCurrentChosenIp()) == 0 && this->port == (g->getCurrentChosenPort()))
            {
                serverFound = true;
                return;
            }

            //from bottom
            hnd->setCursorPos(SERVER_LIST_LAST_ENTRY_X,SERVER_LIST_LAST_ENTRY_Y - (i * SERVER_LIST_NEXT_ENTRY_Y));
            Sleep(5);
            hnd->fireMouseClick(MOUSE_LEFT_CLICK);
            Sleep(SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ);
			std::cout << g->getCurrentChosenIp() << "::" << g->getCurrentChosenPort() << "\n\n";
			//if we found it
			if ((this->ip).compare(g->getCurrentChosenIp()) == 0 && this->port == (g->getCurrentChosenPort()))
			{
				serverFound = true;
				return;
			}
        }

        //perform scrolldowns
        for(int i = 0; i < SERVER_LIST_INFO_SCROLLDOWN_STEPS; i++ ) hnd->fireMouseClick(MOUSE_SCROLL_DOWN);
        Sleep(CLICK_WAIT_TIME);
        Sleep(CLICK_WAIT_TIME);
        Sleep(CLICK_WAIT_TIME);

    }
}
SSState* SSSServerFinder::next()
{
    SSState* ret = this;
    if(serverFound)
    {
        SSSServerJoiner* newState = new SSSServerJoiner();
        //copy values
		newState->ip = (this->ip);
		newState->iplength = (this->iplength);
		newState->password = (this->password);
		newState->port = (this->port);
		newState->passwordlength = (this->passwordlength);
        ret = newState;
    }
    return ret;
}
