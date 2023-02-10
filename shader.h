#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <string>

class ShaderCompilationInfo : public QOpenGLFunctions_3_3_Core
{
public:
    ShaderCompilationInfo(GLuint shaderID);
    ~ShaderCompilationInfo();

    std::string GetCompileLog() const;
    GLint GetCompileStatus() const;

private:
    GLint m_CompileStatus;
    GLchar* m_CompileLogBuffer;
    GLint m_CompileLogLength;
};



class Shader : public QOpenGLFunctions_3_3_Core
{
public:
    GLuint ID;

    Shader(const char* vertexContent, const char* fragmentContent);
    ~Shader();

    void Enable();
    void Disable();

private:
    ShaderCompilationInfo* m_VertexCompilationInfo;
    ShaderCompilationInfo* m_FragmentCompilationInfo;

    GLuint RegisterShader(const GLchar* shaderSource, const GLenum type);
    GLuint CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID);
};

#endif // SHADER_H
