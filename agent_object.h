#pragma once
#include "glad.h"
#include <glm/glm.hpp>
 
#include "game_object.h"
#include "colony_object.h"
#include <vector>

class AgentObject : public GameObject
{
    private: 
        std::vector<float> colony_distance;
        std::vector<ColonyObject>& colonies;
        
        int colony_aim_index = 0;
        

        bool handleColonyCollision();
        bool handleBorderCollision(unsigned int window_width, unsigned int window_height);
        void updateColonyDistances();
    public:
        // Состояние мяча	
        float Radius;    
        bool inBroadcatingNetwork = false;
        
    
        // Конструкторы
        //AgentObject();
        AgentObject(std::vector<ColonyObject>& colonies, glm::vec2 pos, float radius, glm::vec2 velocity, int colony_aim_index);
    
        // Перемещаем мяч, удерживая его в пределах границ окна (за исключением нижнего края); возвращаем новую позицию
        void move(float dt, unsigned int window_width, unsigned int window_height);
        
        float broadCastDistance(int colony_index);        
        void updateDirection(int colony_num, float broadcasted_distance, glm::vec2 pos, float velocity_factor);

    
        // Возвращаем мяч в исходное состояние с заданным положением и скоростью
        void reset(glm::vec2 position, glm::vec2 velocity);
        void restoreColor();

        void printDistances();
        void printState();
};