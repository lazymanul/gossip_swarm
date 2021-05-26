#pragma once
#include "glad.h"
#include <glm/glm.hpp>
 
#include "game_object.h"


class AgentObject : public GameObject
{
    public:
        // Состояние мяча	
        float Radius;    
        
    
        // Конструкторы
        //AgentObject();
        AgentObject(glm::vec2 pos, float radius, glm::vec2 velocity);
    
        // Перемещаем мяч, удерживая его в пределах границ окна (за исключением нижнего края); возвращаем новую позицию
        void Move(float dt, unsigned int window_width, unsigned int window_height);
    
        // Возвращаем мяч в исходное состояние с заданным положением и скоростью
        void Reset(glm::vec2 position, glm::vec2 velocity);
};