#pragma once
#include "glad.h"
#include <glm/glm.hpp>

#include "sprite_renderer.h"
 
// Контейнерный объект, хранящий все состояния, относящиеся к отдельно взятой игровой сущности
class GameObject
{
public:
    // Состояние объекта
    glm::vec2 position, size, velocity;
    glm::vec3 color;
    float rotation;
    bool isSolid;
    bool destroyed;    
 
    // Конструкторы
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
 
    // Отрисовка спрайта
    virtual void draw(SpriteRenderer &renderer);
};