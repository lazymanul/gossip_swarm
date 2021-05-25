#pragma once

#include <map>
#include <string>
 
#include "glad.h"
#include "shader.h"
 
// Статический одноэлементный класс ResourceManager, содержащий несколько функций для загрузки текстур и шейдеров.
// Каждая загруженная текстура и/или шейдер сохраняются для дальнейшего использования.
// Все функции и ресурсы статичны
class ResourceManager
{
public:
 
    // Хранилище ресурсов
    static std::map<std::string, Shader> Shaders;    
 
    // Загружаем (и генерируем) шейдерную программу из файла загрузки исходного кода вершинных, фрагментных (и геометрических) шейдеров.
    // Если gShaderFile != nullptr, то также загружается и геометрический шейдер
    static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
 
    // Получаем сохраненный шейдер
    static Shader GetShader(std::string name);    
 
    // Корректное освобождение памяти всех загруженных ресурсов
    static void Clear();
private:
    // private-конструктор, т.к. мы не хотим, чтобы создавались реальные объекты менеджера ресурсов. Его члены и функции должны быть общедоступными (статичными)
    ResourceManager() { }
 
    // Загружаем и генерируем шейдер из файла
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
};