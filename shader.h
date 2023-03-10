#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QFile>

#include <string>
#include <iostream>

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


class ShaderProgram : public QOpenGLFunctions_3_3_Core
{
public:
    GLuint ID;

    ShaderProgram();
    ~ShaderProgram();

    const ShaderCompilationInfo* GetVertexShaderCompilation() const;
    const ShaderCompilationInfo* GetFragmentShaderCompilation() const;

    void Enable();
    void Disable();

private:
    ShaderCompilationInfo* m_VertexCompilationInfo;
    ShaderCompilationInfo* m_FragmentCompilationInfo;

    std::string m_VertexShaderSource;
    std::string m_FragmentShaderSource;

    const std::string ReadShaderFile(const QString resourcePath) const;
    GLuint RegisterShader(const GLchar* shaderSource, const GLenum type);
    GLuint CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID);
};

#endif // SHADER_H
