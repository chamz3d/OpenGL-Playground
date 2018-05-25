#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "ShaderFile.h"

class Shader
{
private:
    std::vector<ShaderFile> *m_shaderContent;
    std::vector<unsigned int> m_shaders;

public:
    // the shader program ID
    unsigned int ID;

    Shader(std::vector<ShaderFile> &shadersPathAndType);

    void compile();
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    const std::string readShaderCode(const GLchar *path) const;
    unsigned int compileShader(const char *code, GLenum type) const;
    void linkShaders(std::vector<unsigned int> shaders);
};

#endif