#include "glrenderwidget.h"
#include "vbo.h"
#include "ebo.h"
#include "vao.h"

#include <string>

GLfloat vertices[] =
{
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 0.0f
};

GLuint indices[] =
{
    0, 2, 1,
    0, 3, 2
};

GLRenderWidget::GLRenderWidget(QWidget *parent)
    : QOpenGLWidget { parent }
{
}

GLRenderWidget::~GLRenderWidget()
{
    delete vbo;
    delete ebo;
    delete vao;
    delete m_Texture;
    delete m_Shaders;
}

void GLRenderWidget::initializeGL()
{
    // Init opengl
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    std::cout << "Initialized OpenGL widget with version: " << glGetString(GL_VERSION) << std::endl;

    // Create Shader Program
    m_Shaders = new ShaderProgram();

    // Create 2D shape
    vao = new VAO();
    vao->Bind();

    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices, sizeof(indices));

    vao->LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao->LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao->LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    // Create Texture
    m_Texture = new Texture(":/Textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    m_Texture->AssignTextureUnit(m_Shaders, "tex0", 0);
}

void GLRenderWidget::paintGL()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Shaders->Enable();

    m_Texture->Bind();
    vao->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GLRenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
}
