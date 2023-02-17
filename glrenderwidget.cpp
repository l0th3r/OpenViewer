#include "glrenderwidget.h"
#include "vbo.h"
#include "ebo.h"
#include "vao.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat vertices[] =
{
    -0.5f,  0.0f,   0.5f,       0.83f, 0.70f, 0.44f,       0.0f, 0.0f,
    -0.5f,  0.0f,   -0.5f,      0.83f, 0.70f, 0.44f,       5.0f, 0.0f,
    0.5f,   0.0f,   -0.5f,      0.83f, 0.70f, 0.44f,       0.0f, 0.0f,
    0.5f,   0.0f,   0.5f,       0.83f, 0.70f, 0.44f,       5.0f, 0.0f,
    0.0f,   0.8f,   0.0f,       0.92f, 0.86f, 0.76f,       2.5f, 5.0f
};

GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

GLRenderWidget::GLRenderWidget(QWidget *parent)
    : QOpenGLWidget { parent } {}

void GLRenderWidget::Update()
{
    update();
}

void GLRenderWidget::initializeGL()
{
    // Init opengl
    initializeOpenGLFunctions();
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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

    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao->LinkAttrib(*vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    // Create Texture
    m_Texture = new Texture(":/Textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_BGRA, GL_UNSIGNED_BYTE);
    m_Texture->AssignTextureUnit(*m_Shaders, "tex0", 0);

    m_Rotation = 0.0f;
    m_PrevTime = QTime::currentTime();
}

void GLRenderWidget::paintGL()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_Shaders->Enable();

    QTime crntTime = QTime::currentTime();
    if (crntTime.msecsSinceStartOfDay() - m_PrevTime.msecsSinceStartOfDay() >= 5)
    {
        m_Rotation += 0.5f;
        m_PrevTime = crntTime;
    }

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(m_Rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    proj = glm::perspective(glm::radians(45.0f), (float)(this->size().width()/this->size().width()), 0.1f, 100.0f);

    int modelMtxId = glGetUniformLocation(m_Shaders->ID, "mtx_model");
    glUniformMatrix4fv(modelMtxId, 1, GL_FALSE, glm::value_ptr(model));

    int viewMtxId = glGetUniformLocation(m_Shaders->ID, "mtx_view");
    glUniformMatrix4fv(viewMtxId, 1, GL_FALSE, glm::value_ptr(view));

    int projMtxId = glGetUniformLocation(m_Shaders->ID, "mtx_proj");
    glUniformMatrix4fv(projMtxId, 1, GL_FALSE, glm::value_ptr(proj));

    m_Texture->Bind();
    vao->Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

    m_Texture->Unbind();
    vao->Unbind();
}

GLRenderWidget::~GLRenderWidget()
{
    delete vbo;
    delete ebo;
    delete vao;
    delete m_Texture;
    delete m_Shaders;
}
