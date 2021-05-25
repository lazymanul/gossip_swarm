#include "ball_object.h"
#include <iostream>
 
BallObject::BallObject() 
    : GameObject(), Radius(12.5f) {}
 
BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity)
    : GameObject(pos, glm::vec2(radius, radius), glm::vec3(1.0f), velocity), Radius(radius) {}
 
glm::vec2 BallObject::Move(float dt, unsigned int window_width, unsigned int window_height)
{    
    //std::cout << "Vel " << this->Velocity.x << " " << this->Velocity.y << std::endl;
    //std::cout << "Pos " << this->Position.x << " " << this->Position.y << std::endl;
    

    // то перемещаем мяч
    this->Position += this->Velocity * dt;
 
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
    
    return this->Position;
}
 
// Сбрасываем мяч в стартовое положение (если мяч находится за пределами границ окна)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;    
}