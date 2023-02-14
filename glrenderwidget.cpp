#include "glrenderwidget.h"
#include "utils.h"
#include "vbo.h"
#include "ebo.h"
#include "vao.h"

GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        0.8f, 0.3f, 0.2f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,         0.8f, 0.3f, 0.2f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,      0.5f, 0.0f, 0.0f,
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,     0.8f, 0.3f, 0.2f,
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,      0.8f, 0.3f, 0.2f,
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,         0.8f, 0.3f, 0.2f
};

GLuint indices[] =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

GLRenderWidget::GLRenderWidget(QWidget *parent)
    : QOpenGLWidget { parent }
{
}

GLRenderWidget::~GLRenderWidget()
{
    m_Shaders->Disable();
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
}

void GLRenderWidget::paintGL()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Create render objects
    VAO* vao = new VAO();
    vao->Bind();

    VBO* vbo = new VBO(vertices, sizeof(vertices));
    EBO* ebo = new EBO(indices, sizeof(indices));

    vao->LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao->LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    m_Shaders->Enable();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    delete vbo;
    delete ebo;
    delete vao;
}

void GLRenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
}

void GLRenderWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    r = normalize(C.red(), 1.0f, 255.0f);
    g = normalize(C.green(), 1.0f, 255.0f);
    b = normalize(C.blue(), 1.0f, 255.0f);
}
