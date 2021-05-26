#include "swarm_object.h"
#include <iostream>
#include <cstdlib>
 
SwarmObject::SwarmObject(int swarm_size, float radius) : swarm_size(swarm_size)
{    
    for (auto i = 0; i < swarm_size; ++i) {
        glm::vec2 pos = glm::vec2(std::rand() % 1024, std::rand() % 768);
        glm::vec2 vel = glm::vec2(std::rand() % 1024 - 512, std::rand() % 768 - 384) * 0.2f;
        swarm.emplace_back(AgentObject(pos, radius, vel));
    }
}
 
void SwarmObject::Move(float dt, unsigned int window_width, unsigned int window_height)
{       
    for (auto it = std::begin(swarm); it != std::end(swarm); ++it) {
        it->Move(dt, window_width, window_height);
    }
}

void SwarmObject::Draw(SpriteRenderer& renderer)
{
    //std::cout << "position: (" << this->Position.x << ", " << this->Position.y << ")" << std::endl;
    for (auto it = std::begin(swarm); it != std::end(swarm); ++it) {    
        it->Draw(renderer);
    }    
}
 

void SwarmObject::Reset()
{   
}