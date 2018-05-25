#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>

#include "stb_image.h"

class Texture
{
private:
    unsigned char *m_data;
public:
    Texture();
    ~Texture();
    void generateData(const char *path);
};

#endif // TEXTURE_H