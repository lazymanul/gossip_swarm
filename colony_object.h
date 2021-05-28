#pragma once
#include "glad.h"
#include <glm/glm.hpp>
 
#include "game_object.h"
 
 
// Класс BallObject получен из класса GameObject.
// Помимо необходимой информации о состоянии мяча в этом классе присутствуют некоторые дополнительные функции
class ColonyObject : public GameObject
{
    public:
        // Состояние мяча	
        float Radius;    
    
        // Конструкторы
        ColonyObject();
        ColonyObject(glm::vec2 pos, float radius, glm::vec2 velocity, glm::vec3 color);

        bool isAgentCollision(const glm::vec2& pos);
    
        // Возвращаем мяч в исходное состояние с заданным положением и скоростью
        void reset(glm::vec2 position, glm::vec2 velocity);
};