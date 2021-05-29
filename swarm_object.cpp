#include "swarm_object.h"
#include "broadcasting_network.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
 
SwarmObject::SwarmObject(const glm::ivec4& world_frame, int swarm_size, float agent_radius, int num_colonies, int colony_radius) : 
                            world_frame(world_frame), swarm_size(swarm_size), num_colonies(num_colonies)
{
    for (auto i = 0; i < num_colonies; ++i) 
    {
        glm::vec2 pos = glm::vec2(std::rand() % world_frame[2], std::rand() %  world_frame[3]);        
        glm::vec2 vel = glm::vec2(0, 0);
        glm::vec3 color = glm::vec3(std::rand() / (float) RAND_MAX, std::rand() / (float) RAND_MAX, std::rand() / (float) RAND_MAX);
        colonies.emplace_back(ColonyObject(pos, colony_radius, vel, color));
    }

    velocity_factor = world_frame[3] / (agent_radius * agent_radius);
    

    for (auto i = 0; i < swarm_size; ++i) 
    {
        glm::vec2 pos = glm::vec2(std::rand() % world_frame[2], std::rand() %  world_frame[3]);        
        glm::vec2 vel = glm::vec2(std::rand() % world_frame[2] - world_frame[2] / 2, std::rand() % world_frame[3] - world_frame[3] / 2);
        int colony_aim_index = std::rand() % num_colonies;    
        swarm.emplace_back(AgentObject(colonies, pos, agent_radius, velocity_factor * glm::normalize(vel), colony_aim_index));
    }    
}
 
void SwarmObject::move(float dt)
{       
    // int broadcating = (int) 0.1 * swarm_size;
    // for (auto i = 0; i < broadcating; ++i)
    // {        
        float currentTime = glfwGetTime();
        if (currentTime - lastBroadcastTime > 2.0f)
        {

            
            // int broadcasting_agent = std::rand() % swarm_size;
            // float distance = swarm[broadcasting_agent].broadCastDistance(colony_index);            
            //swarm[broadcasting_agent].color = glm::vec3(0.0f, 1.0f, 0.0f);

            //стоит попробовать инкрементальное обновление по типу остовного дерева
            /* for (auto i = 0; i < swarm_size; ++i) 
            {                   
                float distance = swarm[i].broadCastDistance(colony_index);
                for (auto it = std::begin(swarm); it != std::end(swarm); ++it) 
                {
                    it->updateDirection(colony_index, distance, swarm[i].position, velocity_factor);
                }                
            }*/
            
                int colony_index = std::rand() % num_colonies;
                int agent_index = std::rand() % swarm_size;
                BroadcastingNetwork broadNetwork(swarm_size);
                swarm[agent_index].color = glm::vec3(0, 1, 0);
                broadNetwork.buildBroadcastingNetwork(swarm, agent_index, colony_index, 250.0f);
                
            
            //broadNetwork.printGraph();

            lastBroadcastTime = currentTime;
        }

        
    // }    
    for (auto it = std::begin(swarm); it != std::end(swarm); ++it) 
    {
        it->move(dt, world_frame[2], world_frame[3]); 
        if (currentTime - lastBroadcastTime > 0.5f) it->restoreColor();       
    }
}

void SwarmObject::draw(SpriteRenderer& renderer)
{
    //std::cout << "position: (" << this->position.x << ", " << this->position.y << ")" << std::endl;
    for (auto i = 0; i < swarm_size; ++i) 
    {   
        swarm[i].draw(renderer);        
    }    
    for (auto it = std::begin(colonies); it != std::end(colonies); ++it) 
    {
        it->draw(renderer);
    }
}
 

void SwarmObject::reset() {}