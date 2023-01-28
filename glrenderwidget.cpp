#include "glrenderwidget.h"

GLRenderWidget::GLRenderWidget(QWidget *parent)
    : QOpenGLWidget { parent }
{
}

void GLRenderWidget::initializeGL()
{
    float r, g, b, a = 1.0f;

    // Get rgb background color values
    qColorToRGB(Qt::black, r, g, b);

    // Init opengl
    this->initializeOpenGLFunctions();

    // Clear and paint background
    this->glClearColor(r, g, b, a);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    std::cout << "Initialized OpenGL widget with version: " << glGetString(GL_VERSION) << std::endl;
}

void GLRenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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
}

void GLRenderWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    r = normalize(C.red(), 1.0f, 255.0f);
    g = normalize(C.green(), 1.0f, 255.0f);
    b = normalize(C.blue(), 1.0f, 255.0f);
}
