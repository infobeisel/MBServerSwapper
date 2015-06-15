#include "ServerGraph.h"
#include <iostream>
#include <sstream>
ServerGraph::ServerGraph()
{
    //ctor
}

ServerGraph::~ServerGraph()
{
    //dtor
}

void ServerGraph::setUpGraph(FileParser* parser)
{
	parser->openFile(SERVER_GRAPH_URL);
    std::vector<std::string> res = parser->readEntries();
    graph = new  std::map<std::string,std::vector<std::string>>();

    //iterator over read entries
    std::vector<std::string>::iterator it = res.begin();
    //until the end
    while(it != res.end())
    {
        //take as key
        std::string key = *it;
        std::cout << "key: " << *it << " vals:  ";
        std::advance(it,1);
        //take as value
        std::vector<std::string> val;
        for(int i=0; i < FILE_NUM_COLUMNS - 1 && it != res.end(); i++)
        {
            std::cout << *it << "   ";
            val.insert(val.end(),*it);
            std::advance(it,1);
        }
        std::cout << "\n" ;
        graph->insert( std::make_pair(key, val) );
    }

    parser->closeFile();


}

std::string ServerGraph::traverseGraph(std::string currentNodeId, int travelDirection) {

      std::cout << "graph, gimme  " << currentNodeId << "\n";
      std::vector<std::string> val;
      try {
        val=graph->at(currentNodeId);
      }
      catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        return "";
      }

    std::string ret;
    switch(travelDirection) {
        case TRAVEL_DIR_NOOP: ret = currentNodeId;    break;
        case TRAVEL_DIR_NORTH:ret = val.at(FILE_COLUMN_TO_NORTH_INDEX);         break;
        case TRAVEL_DIR_EAST: ret = val.at(FILE_COLUMN_TO_EAST_INDEX);         break;
        case TRAVEL_DIR_SOUTH:ret = val.at(FILE_COLUMN_TO_SOUTH_INDEX);         break;
        case TRAVEL_DIR_WEST: ret = val.at(FILE_COLUMN_TO_WEST_INDEX);         break;
    }


    return ret;

}
std::string ServerGraph::getIp(std::string nodeId) {
        std::vector<std::string> val=graph->at(nodeId);
        return (val.at(FILE_COLUMN_IP_INDEX));
}
int ServerGraph::getPort(std::string nodeId) {
	std::vector<std::string> val = graph->at(nodeId);
	return std::stoi(val.at(FILE_COLUMN_PORT_INDEX));
}



std::string ServerGraph::getNodeIdFromMapName(std::string mapName) {
    std::map<std::string,std::vector<std::string>>::iterator it = graph->begin();
    int nodeindex = 0;//as maps are ordered (constantly iterate over same arrangement of elemts) we can simply increment this
    std::vector<std::string> val;
    while(it != graph->end()) {
        val = it->second;
        std::string curName = val.at(FILE_COLUMN_MAP_NAME_INDEX);
        std::cout << "temp curName |" << curName <<"|  wanted: |" << mapName << "|\n";
        if((curName.compare(mapName)) == 0) break;
        nodeindex++;
        std::advance(it,1);
    }
    std::ostringstream  convert;
    convert << nodeindex;

    return convert.str();

}
