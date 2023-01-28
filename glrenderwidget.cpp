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
    glEnable(GL_COLOR_MATERIAL);
}

void GLRenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GLRenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLRenderWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    r = normalize(C.red(), 1.0f, 255.0f);
    g = normalize(C.green(), 1.0f, 255.0f);
    b = normalize(C.blue(), 1.0f, 255.0f);
}
