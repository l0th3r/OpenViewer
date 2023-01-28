#ifndef GLRENDERWIDGET_H
#define GLRENDERWIDGET_H

#include "utils.h"

#include <QColor>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <iostream>

class GLRenderWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLRenderWidget(QWidget *parent = nullptr);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void loadShadersGL();
private:
    QWidget* m_LoadingPanel;

    void qColorToRGB(const QColor &C, float &r, float &g, float &b) const;
};

#endif // GLRENDERWIDGET_H
