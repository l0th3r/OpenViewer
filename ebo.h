#ifndef EBO_H
#define EBO_H

#include <QOpenGLFunctions_3_3_Core>

class EBO : public QOpenGLFunctions_3_3_Core
{
public:
    GLuint ID;

    EBO(GLuint* indices, GLsizeiptr size);
    ~EBO();

    void Bind();
    void Unbind();
    void Delete();
};

#endif // EBO_H
