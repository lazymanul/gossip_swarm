#include "swarm_object.h"
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
        if (currentTime - lastBroadcastTime > 0.1f)
        {
            

            //broadcasting_agent = std::rand() % swarm_size;
            //glm::ivec2 distance_data = swarm[broadcasting_agent].broadCastDistance();
            //swarm[broadcasting_agent].color = glm::vec3(0.0f, 1.0f, 0.0f);
            int colony_info_index = std::rand() % num_colonies;
            for (auto i = 0; i < swarm_size; ++i) 
            {   
                glm::ivec2 distance_data = swarm[i].broadCastDistance(colony_info_index);
                for (auto it = std::begin(swarm); it != std::end(swarm); ++it) 
                {
                    it->updateDirection(distance_data[0], distance_data[1], swarm[i].position, velocity_factor);
                }                
            }
            lastBroadcastTime = currentTime;
        }

        
    // }
    
    for (auto it = std::begin(swarm); it != std::end(swarm); ++it) 
    {
        it->move(dt, world_frame[2], world_frame[3]);
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