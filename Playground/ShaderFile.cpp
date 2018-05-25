#include "ShaderFile.h"

ShaderFile::ShaderFile(const char *path, GLenum type)
{
    m_path = path;
    m_type = type;
}

GLenum ShaderFile::Type() const { return m_type; }
void ShaderFile::Type(GLenum val) { m_type = val; }

const char* ShaderFile::Path() const { return m_path; }
void ShaderFile::Path(const char* val) { m_path = val; }