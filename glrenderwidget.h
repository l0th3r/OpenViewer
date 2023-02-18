#ifndef GLRENDERWIDGET_H
#define GLRENDERWIDGET_H

#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "vbo.h"
#include "ebo.h"
#include "vao.h"

#include <QApplication>
#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QTime>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QCursor>

#include <iostream>

class GLRenderWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    GLRenderWidget(QWidget *parent = nullptr);
    ~GLRenderWidget();

    void Start();

public slots:
    void Update();

protected:    
    void initializeGL() override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    ShaderProgram* m_Shaders;
    Camera* m_Camera;

    // TEMP
    Texture* m_Texture;
    VBO* vbo;
    EBO* ebo;
    VAO* vao;

    // Inputs
    bool m_NeedMouseTracking;
    QPointF m_MouseStartPosition;
    QPointF m_MousePosition;
    int m_RequestedZoom;

    void ManageCameraInput();
};

#endif // GLRENDERWIDGET_H
