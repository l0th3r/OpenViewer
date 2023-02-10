#ifndef GLRENDERWIDGET_H
#define GLRENDERWIDGET_H

#include "shader.h"

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <iostream>

class GLRenderWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    GLRenderWidget(QWidget *parent = nullptr);
    ~GLRenderWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    // Store shader program
    Shader* m_Shaders;

    // TEMP
    GLfloat *m_Vertices;

private:
    QWidget* m_LoadingPanel;

    void qColorToRGB(const QColor &C, float &r, float &g, float &b) const;
};

#endif // GLRENDERWIDGET_H
