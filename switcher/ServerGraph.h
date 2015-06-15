#ifndef SERVERGRAPH_H
#define SERVERGRAPH_H
#include "FileParser.h"
#include <map>
class ServerGraph
{
    public:
        ServerGraph();
        virtual ~ServerGraph();
        void setUpGraph(FileParser* parser);
        /** returns the key to the node in the graph, which comes after given current node id into given travelDir **/
        std::string traverseGraph(std::string currentNodeId, int travelDirection);

        //std::string getMapName(std::string nodeId);
        std::string getNodeIdFromMapName(std::string mapName);
        std::string getIp(std::string nodeId);
		int getPort(std::string nodeId);

    protected:
    private:
        std::map<std::string,std::vector<std::string>>* graph;
};

#endif // SERVERGRAPH_H
