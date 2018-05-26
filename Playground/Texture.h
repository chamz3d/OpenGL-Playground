#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>

#include "stb_image.h"

class Texture
{
private:
    std::string m_path;
public:
    Texture(const char* path);
    void generateData();
};

#endif // TEXTURE_H