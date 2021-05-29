#pragma once
#include <vector>
#include "agent_object.h"

class BroadcastingNetwork 
{
    private:
        int N;
        std::vector<std::vector<int>> broadcastingGraph;


    public:
        BroadcastingNetwork(int N);

        void addEdge(int start, int end);
        void printGraph();

        void buildBroadcastingNetwork(std::vector<AgentObject>& swarm, int origin_agent,  int colony_index, float broadcastingDistance);
};