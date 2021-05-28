#include "ball_object.h"
#include <iostream>
 
BallObject::BallObject() 
    : GameObject(), Radius(12.5f) {}
 
BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity)
    : GameObject(pos, glm::vec2(radius, radius), glm::vec3(1.0f), velocity), Radius(radius) {}
 
glm::vec2 BallObject::move(float dt, unsigned int window_width, unsigned int window_height)
{    
    //std::cout << "Vel " << this->velocity.x << " " << this->velocity.y << std::endl;
    //std::cout << "Pos " << this->position.x << " " << this->position.y << std::endl;
    

    // то перемещаем мяч
    this->position += this->velocity * dt;
 
    // Затем проверяем, находится ли он за пределами границ окна, и если да, то изменяем его скорость и восстанавливаем правильное положение
    if (this->position.x - size.x <= 0.0f)
    {
        this->velocity.x = -this->velocity.x;
        this->position.x = size.x;
    }
    else if (this->position.x + this->size.x >= window_width)
    {
        this->velocity.x = -this->velocity.x;
        this->position.x = window_width - this->size.x;
    }

    if (this->position.y - size.y <= 0.0f)
    {
        this->velocity.y = -this->velocity.y;
        this->position.y = size.y;
    } 
    else if (this->position.y + this->size.y >= window_height) 
    {
        this->velocity.y = -this->velocity.y;
        this->position.y = window_height - this->size.y; 
    }
    
    return this->position;
}
 
// Сбрасываем мяч в стартовое положение (если мяч находится за пределами границ окна)
void BallObject::reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;    
}