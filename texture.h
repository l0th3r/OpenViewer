#ifndef TEXTURE_H
#define TEXTURE_H

#include "shader.h"

#include <QImage>
#include <QOpenGLFunctions_3_3_Core>

class Texture : public QOpenGLFunctions_3_3_Core
{
public:
    GLuint ID;
    GLenum m_Type;

    Texture(const char* resourcePath, GLenum type, GLenum slot, GLenum format, GLenum pixelType);
    ~Texture();

    void AssignTextureUnit(ShaderProgram* program, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();

private:
    const char* m_ResourcePath;
};

#endif // TEXTURE_H
