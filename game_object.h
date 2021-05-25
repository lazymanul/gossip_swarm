#pragma once
#include "glad.h"
#include <glm/glm.hpp>

#include "sprite_renderer.h"
 
// Контейнерный объект, хранящий все состояния, относящиеся к отдельно взятой игровой сущности
class GameObject
{
public:
    // Состояние объекта
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    float Rotation;
    bool IsSolid;
    bool Destroyed;    
 
    // Конструкторы
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
 
    // Отрисовка спрайта
    virtual void Draw(SpriteRenderer &renderer);
};