#ifndef SHADER_FILE_H
#define SHADER_FILE_H

#include <glad/glad.h>

struct ShaderFile
{
private:
    const char* m_path;
    GLenum m_type;

public:
    ShaderFile(const char* path, GLenum type);

    GLenum Type() const;
    void Type(GLenum val);

    const char* Path() const;
    void Path(const char* val);
};

#endif // SHADER_FILE_H
