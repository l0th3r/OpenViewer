#ifndef VAO_H
#define VAO_H

#include "vbo.h"

#include <QOpenGLFunctions_3_3_Core>

class VAO : public QOpenGLFunctions_3_3_Core
{
public:
    GLuint ID;

    VAO();
    void LinkVBOLayout(VBO vbo, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_H
