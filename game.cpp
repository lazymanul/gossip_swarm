#include "game.h"
#include "resource_manager.h"
#include <iostream>
 

Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_READY), Keys(), Width(width), Height(height) 
{ 
 
}
 
Game::~Game() 
{    
    
}
 
void Game::Init() 
{
     // Загрузка шейдеров
    ResourceManager::LoadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
 
    // Конфигурирование шейдеров
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

    // В таких местах, возможно, хочется использовать shared_ptr    
    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    
    // Установка специфичных для рендеринга элементов управления
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    std::srand(14);
    Swarm = new SwarmObject(glm::ivec4(0, 0, Width, Height), 280, 4.0f, 3, 40.0f);
}

void Game::Stop() 
{
    delete Renderer;    
    delete Swarm;
}
 
void Game::Update(float dt) 
{    
    if (this->State == GAME_ACTIVE) {        
        Swarm->move(dt);
    }
}
 
void Game::ProcessInput(float dt) 
{    
    if (this->Keys[GLFW_KEY_S])
    {
        this->State = GAME_ACTIVE;
    }
    if (this->Keys[GLFW_KEY_P]) {
        this->State = GAME_PAUSED;
    }

}
 
void Game::Render() 
{
    //std::cout << "Scene render" << std::endl;                            
    Swarm->draw(*Renderer);
}