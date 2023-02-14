#include "vao.h"

VAO::VAO()
{
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    Delete();
    Unbind();
}

void VAO::LinkVBOLayout(VBO* vbo, GLuint layout)
{
    vbo->Bind();

    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(layout);

    vbo->Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}
