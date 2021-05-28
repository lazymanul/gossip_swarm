#pragma once
#include "glad.h"
#include <glm/glm.hpp>
#include <vector>
 
#include "agent_object.h"
#include "colony_object.h"

// Класс BallObject получен из класса GameObject.
// Помимо необходимой информации о состоянии мяча в этом классе присутствуют некоторые дополнительные функции
class SwarmObject
{
    private:        
        glm::ivec4 world_frame;     

        int swarm_size = 0;   
        std::vector<AgentObject> swarm;
        int agent_radius;

        int num_colonies = 0;
        std::vector<ColonyObject> colonies;
        int colony_radius;        
        
        float velocity_factor = 1.0f;
        float lastBroadcastTime = 0;
    public:        
        
        
    
        // Конструкторы
        //SwarmObject();
        SwarmObject(const glm::ivec4& world_frame, int swarm_size, float agent_radius, int num_colonies, int colony_radius);
        
        void move(float dt);
        void draw(SpriteRenderer& renderer);
        void reset();
}; 