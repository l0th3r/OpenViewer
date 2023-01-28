#include "glrenderwidget.h"

GLRenderWidget::GLRenderWidget(QWidget *parent)
    : QOpenGLWidget { parent }
{
}

GLRenderWidget::~GLRenderWidget()
{
    glDeleteProgram(m_ShaderProgram);
}

void GLRenderWidget::initializeGL()
{
    // Init opengl
    initializeOpenGLFunctions();

    // Clear and paint background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    std::cout << "Initialized OpenGL widget with version: " << glGetString(GL_VERSION) << std::endl;

    this->loadShadersGL();
}

void GLRenderWidget::paintGL()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glUseProgram(m_ShaderProgram);

    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
    };

    GLuint indices[] =
    {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void GLRenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
}

void GLRenderWidget::loadShadersGL()
{
    const char* vertexShaderSource = "#version 3300 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\0";

    const char* fragmentShaderSource = "#version 3300 core\n"
            "out vec4 FragColor;\n"
            "void main() { FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f) }\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, vertexShader);
    glAttachShader(m_ShaderProgram, fragmentShader);
    glLinkProgram(m_ShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout << "Loaded vertex and fragment shader" << std::endl;
}

void GLRenderWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    r = normalize(C.red(), 1.0f, 255.0f);
    g = normalize(C.green(), 1.0f, 255.0f);
    b = normalize(C.blue(), 1.0f, 255.0f);
}
