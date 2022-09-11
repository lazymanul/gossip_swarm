#include "agent_object.h"
#include <iostream>
 
//AgentObject::AgentObject() 
//    : GameObject(), Radius(12.5f) {}
 
AgentObject::AgentObject(std::vector<ColonyObject>& colonies, glm::vec2 pos, float radius, glm::vec2 velocity, int colony_aim_index)
    : GameObject(pos, glm::vec2(radius, radius), colonies[colony_aim_index].color, velocity), 
      Radius(radius),
      colonies(colonies),
      colony_distance((int) colonies.size(), 0),
      colony_aim_index(colony_aim_index)
{}
 

bool AgentObject::handleColonyCollision() 
{
    for (auto i = 0; i < colonies.size(); ++i) 
    {
        if (colonies[i].isAgentCollision(this->position)) 
        {
            //std::cout << "collision detected" << std::endl;           
            
            this->velocity.x = -this->velocity.x;
            this->velocity.y = -this->velocity.y;

            this->colony_distance[i] = 0;

            if (i == colony_aim_index) 
            {
                colony_aim_index = (colony_aim_index + 1) % colonies.size();
                color = colonies[colony_aim_index].color;
            }

            return true;
        }
        
    }
    return false;
}

bool AgentObject::handleBorderCollision(unsigned int window_width, unsigned int window_height) 
{
    bool isBorderCollision = false;
    if (this->position.x - size.x <= 0.0f)
    {
        this->velocity.x = -this->velocity.x;
        this->position.x = size.x;
        isBorderCollision = true;
    }
    else if (this->position.x + this->size.x >= window_width)
    {
        this->velocity.x = -this->velocity.x;
        this->position.x = window_width - this->size.x;
        isBorderCollision = true;
    }

    if (this->position.y - size.y <= 0.0f)
    {
        this->velocity.y = -this->velocity.y;
        this->position.y = size.y;
        isBorderCollision = true;
    } 
    else if (this->position.y + this->size.y >= window_height) 
    {
        this->velocity.y = -this->velocity.y;
        this->position.y = window_height - this->size.y; 
        isBorderCollision = true;        
    }
    return isBorderCollision;
}

void AgentObject::updateColonyDistances() 
{
    for (auto i = 0; i < colony_distance.size(); ++i) 
    {
        colony_distance[i] += glm::length(this->velocity); 
    }    
}

void AgentObject::printDistances() 
{
    std::cout << this << ": ";
    for (auto i = 0; i < colony_distance.size(); ++i) 
    {
        std::cout << colony_distance[i] << " ";
    }
    std::cout << std::endl;
}

void AgentObject::printState()
{
    std::cout << "Pos: (" << position.x << ", " << position.y << ") ";
    std::cout << "Vel: (" << velocity.x << ", " << velocity.y << ") ";
    std::cout << "Aim: (" << colony_aim_index << ")" << std::endl;
}

float AgentObject::broadCastDistance(int colony_index) 
{    
    return colony_distance[colony_index] + 100;
}

void AgentObject::updateDirection(int colony_num, float broadcasted_distance, glm::vec2 pos, float velocity_factor) 
{
    if ((glm::length(pos - position) < 80.0f) && (glm::length(pos - position) > 1.0f))
    {    
        if (broadcasted_distance < colony_distance[colony_num])
        {
            colony_distance[colony_num] = broadcasted_distance;
            
            if (colony_num == colony_aim_index) 
            {        
                velocity = glm::normalize(pos - position) * velocity_factor;
                //printState();         
            }
            
        }
    }      
}

void AgentObject::restoreColor() 
{
    this->color = colonies[colony_aim_index].color;
}

void AgentObject::move(float dt, unsigned int window_width, unsigned int window_height)
{   
    //добавить вращение вектора на небольшой угол            
    //float alpha = (std::rand() / 30.0f - 15.0f) * 3.14 / 180; 
    this->position += this->velocity * dt;
    this->inBroadcatingNetwork = false;
    
    updateColonyDistances();
    handleColonyCollision();
    handleBorderCollision(window_width, window_height);
    //printDistances();
}
 
void AgentObject::reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;    
}