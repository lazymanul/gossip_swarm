#include "colony_object.h"
#include <iostream>
 
ColonyObject::ColonyObject() 
    : GameObject(), Radius(12.5f) {}
 
ColonyObject::ColonyObject(glm::vec2 pos, float radius, glm::vec2 velocity, glm::vec3 color)
    : GameObject(pos, glm::vec2(radius, radius), glm::vec3(color), velocity), Radius(radius) {} 

bool ColonyObject::isAgentCollision(const glm::vec2& pos) {
    float dx = this->position.x - pos.x;
    float dy = this->position.y - pos.y;
    return (dx * dx + dy * dy)  <= Radius * Radius;
}
 
// Сбрасываем мяч в стартовое положение (если мяч находится за пределами границ окна)
void ColonyObject::reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;    
}