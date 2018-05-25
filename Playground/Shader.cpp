#include "Shader.h"

Shader::Shader(std::vector<std::pair<const GLchar*, GLenum>> &shadersPathAndType)
{
    m_shadersContent = &shadersPathAndType;
}

void Shader::compile()
{
    std::for_each(m_shadersContent->begin(), m_shadersContent->end(), [&](const std::pair<const GLchar*, GLenum> shaderPathAndType)
    {
        const std::string shaderStr = readShaderCode(shaderPathAndType.first);
        unsigned int shaderId = compileShader(shaderStr.c_str(), shaderPathAndType.second);
        m_shaders.push_back(shaderId);
    });
    linkShaders(m_shaders);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 

const std::string Shader::readShaderCode(const GLchar* path) const
{
    std::string code;
    std::ifstream file;
    std::stringstream stream;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << e.code() << std::endl;
    }

    return code;
}

unsigned int Shader::compileShader(const char* code, GLenum type) const
{
    unsigned int shader = -1;
    int success;
    char infoLog[512];

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    // print compile errors if any
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    return shader;
}

void Shader::linkShaders(std::vector<unsigned int> shaders)
{
    int success;
    char infoLog[512];
    ID = glCreateProgram();

    std::for_each(shaders.begin(), shaders.end(), [&](unsigned int shader)
    {
        glAttachShader(ID, shader);

        glLinkProgram(ID);

        // print linking errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // delete the shader as it's linked into the program now and is no longer necessary
        glDeleteShader(shader);
    });
}
