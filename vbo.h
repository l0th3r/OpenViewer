#ifndef VBO_H
#define VBO_H

#include <QOpenGLFunctions_3_3_Core>

class VBO : public QOpenGLFunctions_3_3_Core
{
public:
    GLuint ID;

    VBO(GLfloat* vertices, GLsizeiptr size);
    ~VBO();

    void Bind();
    void Unbind();
    void Delete();
};

#endif // VBO_H
