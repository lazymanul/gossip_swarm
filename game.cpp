#include "game.h"
#include "resource_manager.h"
#include "ball_object.h"
#include <iostream>
 
// Радиус мяча 
const float BALL_RADIUS = 12.5f;
// Начальная скорость мяча
const glm::vec2 INITIAL_BALL_VELOCITY(20.0f, -45.0f);


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

    glm::vec2 ballPos = glm::vec2(Width / 2.0f - BALL_RADIUS, Height / 2.0f -BALL_RADIUS);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY);    
}

void Game::Stop() 
{
    delete Renderer;
    delete Ball;
}
 
void Game::Update(float dt) 
{    
    if (this->State == GAME_ACTIVE) {
        Ball->Move(dt, Width, Height);
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
    /*
    Renderer->DrawSprite(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 
                            45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    */                            
    Ball->Draw(*Renderer);
}