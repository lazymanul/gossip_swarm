#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "shader.h"
#include "resource_manager.h"
#include "game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// settings
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);
 
int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, false);
 
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);
 
    // GLAD: загрузка всех указателей на функции OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
 
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
    // Конфигурация OpenGL
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
    // Инициализация игры
    Breakout.Init();
 
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
 
    while (!glfwWindowShouldClose(window))
    {
        // Вычисление дельты времени
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
 
        // Обрабатываем пользовательский ввод с клавиатуры
        Breakout.ProcessInput(deltaTime);
 
        // Обновляем состояние игры
        Breakout.Update(deltaTime);
 
        // Рендер
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();
 
        glfwSwapBuffers(window);
    }
 
    // Освобождение всех ресурсов, загруженных с использованием менеджера ресурсов
    Breakout.Stop();
    ResourceManager::Clear(); 
    glfwTerminate();
    return 0;
}
 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Когда пользователь нажимает клавишу Escape, мы устанавливаем для свойства WindowShouldClose значение true, закрывая приложение
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Breakout.Keys[key] = false;
    }
}
 
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.  
    // Обратите внимание, что ширина и высота будут значительно больше, чем указано, на Retina-дисплеях    
    glViewport(0, 0, width, height);    
}