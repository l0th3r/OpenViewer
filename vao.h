#ifndef VAO_H
#define VAO_H

#include "vbo.h"

#include <QOpenGLFunctions_3_3_Core>

class VAO : public QOpenGLFunctions_3_3_Core
{
public:
    GLuint ID;

    VAO();
    ~VAO();

    void LinkAttrib(VBO* vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_H
