#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions_3_3_Core>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.h"

class Camera : public QOpenGLFunctions_3_3_Core
{
public:
    Camera(int width, int height, glm::vec3 position);
    ~Camera();

    glm::vec3 Position;
    glm::vec3 Orientation;
    glm::vec3 Up;

    float OrbitX;
    float OrbitY;

    int Width;
    int Height;

    float Speed;
    float Sensitivity;

    void Matrix(float FOVdeg, float nearPlane, float farPlane, ShaderProgram& shaderProgram, const char* uniform);
    void UpdateOrbitInput(double mouseX, double mouseY);
    void SetCameraAroundOrigin(float x, float y);
    void ZoomIn();
    void ZoomOut();
};

#endif // CAMERA_H
