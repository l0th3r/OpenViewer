#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    initializeOpenGLFunctions();

    Position = position;
    Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    Up = glm::vec3(0.0f, 1.0f, 0.0f);

    Width = width;
    Height = height;

    Speed = 0.1f;
    Sensitivity = 100.0f;
}

Camera::~Camera()
{
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, ShaderProgram& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    proj = glm::perspective(glm::radians(FOVdeg), (float)(Width / Height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::SetRotation(double mx, double my)
{
    //float rotx = Sensitivity * (float)(my - (Height / 2)) / Height;
    //float roty = Sensitivity * (float)(mx - (Height / 2)) / Height;

}

void Camera::ZoomIn()
{
    Position += Speed * Orientation;
}

void Camera::ZoomOut()
{
    Position += Speed * -Orientation;
}
