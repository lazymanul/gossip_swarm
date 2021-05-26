#include "agent_object.h"
#include <iostream>
 
//AgentObject::AgentObject() 
//    : GameObject(), Radius(12.5f) {}
 
AgentObject::AgentObject(glm::vec2 pos, float radius, glm::vec2 velocity)
    : GameObject(pos, glm::vec2(radius, radius), glm::vec3(1.0f), velocity), Radius(radius) {}
 
void AgentObject::Move(float dt, unsigned int window_width, unsigned int window_height)
{    
    //std::cout << "Vel " << this->Velocity.x << " " << this->Velocity.y << std::endl;
    //std::cout << "Pos " << this->Position.x << " " << this->Position.y << std::endl;    

    glm::vec2 dv = glm::vec2(std::rand() % 1024 - 512, std::rand() % 768 - 384) * 0.08f;    
    this->Position += (this->Velocity + dv) * dt;
 
    // Затем проверяем, находится ли он за пределами границ окна, и если да, то изменяем его скорость и восстанавливаем правильное положение
    if (this->Position.x - Size.x <= 0.0f)
    {
        this->Velocity.x = -this->Velocity.x;
        this->Position.x = Size.x;
    }
    else if (this->Position.x + this->Size.x >= window_width)
    {
        this->Velocity.x = -this->Velocity.x;
        this->Position.x = window_width - this->Size.x;
    }

    if (this->Position.y - Size.y <= 0.0f)
    {
        this->Velocity.y = -this->Velocity.y;
        this->Position.y = Size.y;
    } 
    else if (this->Position.y + this->Size.y >= window_height) 
    {
        this->Velocity.y = -this->Velocity.y;
        this->Position.y = window_height - this->Size.y; 
    }
}
 
// Сбрасываем мяч в стартовое положение (если мяч находится за пределами границ окна)
void AgentObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;    
}