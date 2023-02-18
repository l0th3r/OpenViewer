#include "glrenderwidget.h"

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
    GLRenderWidget::update();
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

    // Create 3D shape
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

    m_Camera = new Camera(this->width(), this->height(), glm::vec3(0.0f, 0.0f, 0.2f));
}

void GLRenderWidget::paintGL()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shaders->Enable();

    m_Camera->Matrix(45.0f, 0.1f, 100.0f, *m_Shaders, "mtx_cam");
    ManageCameraInput();

    m_Texture->Bind();
    vao->Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

    m_Texture->Unbind();
    vao->Unbind();
}

void GLRenderWidget::mousePressEvent(QMouseEvent *event)
{
    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);

    if (event->button() == Qt::MouseButton::LeftButton)
    {
        std::cout << "MOUSE PRESSED" << std::endl;
        m_NeedMouseTracking = true;
        m_MouseStartPosition = event->position();
    }
}

void GLRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_NeedMouseTracking == true)
    {
        m_MousePosition = m_MouseStartPosition - event->position();
        //std::cout << "MOUSE MOVE x=" << m_MousePosition.x() << " y=" << m_MousePosition.y() << std::endl;
    }
}

void GLRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //QApplication::restoreOverrideCursor();
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        std::cout << "MOUSE RELEASE" << std::endl;
        m_NeedMouseTracking = false;
    }
}

void GLRenderWidget::wheelEvent(QWheelEvent* event)
{
    m_RequestedZoom = event->angleDelta().y();
}

void GLRenderWidget::ManageCameraInput()
{
    // Zoom
    m_Camera->Speed = glm::abs(m_RequestedZoom) / 100.0f;

    if (m_RequestedZoom > 0)
    {
        m_Camera->ZoomIn();
    }
    else if (m_RequestedZoom < 0)
    {
        m_Camera->ZoomOut();
    }
    m_RequestedZoom = 0;

    // Orientation
    if(m_NeedMouseTracking == false)
        return;

    m_Camera->SetRotation(m_MousePosition.x(), m_MousePosition.y());
}

GLRenderWidget::~GLRenderWidget()
{
    delete vbo;
    delete ebo;
    delete vao;
    delete m_Texture;
    delete m_Shaders;
}
