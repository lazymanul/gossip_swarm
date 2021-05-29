#include "broadcasting_network.h"
#include <iostream>

BroadcastingNetwork::BroadcastingNetwork(int N) : N(N) 
{
    broadcastingGraph.resize(N);            
}

void BroadcastingNetwork::addEdge(int start, int end) 
{
    broadcastingGraph[start].emplace_back(end);
}

void BroadcastingNetwork::printGraph()
{
    std::cout << "Current network" << std::endl;
    for (int i = 0; i < N; i++) {
        if (broadcastingGraph[i].size() > 0) {
            std::cout << i << " --> ";

            for (int v : broadcastingGraph[i])
                std::cout << v << " ";
            std::cout << std::endl;
        }
    }
}

void BroadcastingNetwork::buildBroadcastingNetwork(std::vector<AgentObject>& swarm, int origin_agent, int colony_index, float broadcastingDistance) {
    //const float broadcastingDistance = 50;
    //int origin_agent = 2;

    std::vector<int> network;
    network.emplace_back(origin_agent);
    int currentNode = 0;
    swarm[origin_agent].inBroadcatingNetwork = true;
    
    float dst = swarm[origin_agent].broadCastDistance(colony_index);

    bool isNetworkChanged = true;
    while (isNetworkChanged || (currentNode < network.size())) {
        isNetworkChanged = false;
        for (auto i = 0; i < swarm.size(); ++i) {
            int nodeIndex = network[currentNode]; 
            if ((!swarm[i].inBroadcatingNetwork) 
                && (glm::length(swarm[i].position - swarm[nodeIndex].position) <= broadcastingDistance)) {
                    isNetworkChanged = true;
                    network.emplace_back(i);
                    swarm[i].inBroadcatingNetwork = true;
                    addEdge(nodeIndex, i);
                    swarm[i].color = glm::vec3(0.3, 0, 0);

                    swarm[i].updateDirection(colony_index, dst, swarm[origin_agent].position, 5.0f);
            }

            dst += broadcastingDistance;
        }
        ++currentNode;
    }
}