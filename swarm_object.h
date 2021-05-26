#pragma once
#include "glad.h"
#include <glm/glm.hpp>
#include <vector>
 
#include "agent_object.h"

// Класс BallObject получен из класса GameObject.
// Помимо необходимой информации о состоянии мяча в этом классе присутствуют некоторые дополнительные функции
class SwarmObject
{
    private:         
        int swarm_size = 0;        
    public:        
        float Radius;
        std::vector<AgentObject> swarm;
    
        // Конструкторы
        //SwarmObject();
        SwarmObject(int swarm_size, float radius);    
        
        void Move(float dt, unsigned int window_width, unsigned int window_height);
        void Draw(SpriteRenderer& renderer);
        void Reset();
}; 