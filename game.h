#pragma once

#include "glad.h"
#include "sprite_renderer.h"
#include "swarm_object.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
 
// Состояния игры
enum GameState {
    GAME_READY,
    GAME_ACTIVE,
    GAME_PAUSED    
};



// Класс Game содержит все связанные с игрой параметры состояния и различный функционал. 
class Game{
    SpriteRenderer* Renderer = nullptr;
    //BallObject *Ball = nullptr; 
    SwarmObject* Swarm = nullptr;

public: 
    // Игровое состояние
    GameState State;	
    bool Keys[1024];
    int Width, Height;
     
    Game(unsigned int width, unsigned int height);
    ~Game();
 
    // Инициализация начального состояния игры (загрузка всех шейдеров, текстур, уровней)
    void Init();
    void Stop();
 
    // Игровой цикл
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};
 
