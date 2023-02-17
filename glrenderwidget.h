#ifndef GLRENDERWIDGET_H
#define GLRENDERWIDGET_H

#include "shader.h"
#include "Texture.h"
#include "vbo.h"
#include "ebo.h"
#include "vao.h"

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QTime>

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

    //void paintEvent(QPaintEvent *e) override;

private:
    // Store shader program
    ShaderProgram* m_Shaders;

    // TEMP
    Texture* m_Texture;
    VBO* vbo;
    EBO* ebo;
    VAO* vao;

    float m_Rotation;
    QTime m_PrevTime;
};

#endif // GLRENDERWIDGET_H
