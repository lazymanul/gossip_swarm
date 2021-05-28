#include "game_object.h"
#include <iostream>

GameObject::GameObject()
    : position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), isSolid(false), destroyed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity)
    : position(pos), size(size), velocity(velocity), color(color), rotation(0.0f), isSolid(false), destroyed(false) { }

void GameObject::draw(SpriteRenderer& renderer)
{
    //std::cout << "position: (" << this->position.x << ", " << this->position.y << ")" << std::endl;
    renderer.DrawSprite(this->position, this->size, this->rotation, this->color);
}