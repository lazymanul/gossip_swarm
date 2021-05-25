#include "resource_manager.h"
 
#include <iostream>
#include <sstream>
#include <fstream>
 
// Создание экземпляров статических переменных
std::map<std::string, Shader> ResourceManager::Shaders;
 
 
Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}
 
Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}
 
void ResourceManager::Clear()
{
    // (корректное) удаление всех шейдеров	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
}
 
Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. Получение исходного кода вершинного и фрагментного шейдеров
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Открываем файлы
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
 
        // Считываем содержимое файлового буфера в соответствующие потоки
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
 
        // Закрываем файлы
        vertexShaderFile.close();
        fragmentShaderFile.close();
 
        // Конвертируем поток в строку
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
 
        // Если присутствует путь геометрического шейдера, то загружаем геометрический шейдер
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
 
    // 2. Теперь создаем объект шейдера из исходного кода
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}