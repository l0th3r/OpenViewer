#include "shader.h"
#include <iostream>

// Shader compilation info class
ShaderCompilationInfo::ShaderCompilationInfo(GLuint shaderID)
{
    initializeOpenGLFunctions();

    // Get shader compilation status
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_CompileStatus);

    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &m_CompileLogLength);

    m_CompileLogBuffer = new GLchar[m_CompileLogLength];
    glGetShaderInfoLog(shaderID, m_CompileLogLength, NULL, m_CompileLogBuffer);
}

ShaderCompilationInfo::~ShaderCompilationInfo()
{
    delete []m_CompileLogBuffer;
}

std::string ShaderCompilationInfo::GetCompileLog() const
{
    std::string log(this->m_CompileLogBuffer);
    return log;
}

GLint ShaderCompilationInfo::GetCompileStatus() const
{
    return m_CompileStatus;
}

// Shader class
Shader::Shader(const char* vertexContent, const char* fragmentContent)
{
    initializeOpenGLFunctions();

    const char* vertexShaderSource = "#version 3300 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\0";

    const char* fragmentShaderSource = "#version 3300 core\n"
            "out vec4 FragColor;\n"
            "void main() { FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f) }\0";

    GLuint vertexShader = RegisterShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = RegisterShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    m_VertexCompilationInfo = new ShaderCompilationInfo(vertexShader);
    m_FragmentCompilationInfo = new ShaderCompilationInfo(fragmentShader);

    std::cout << "Vertex shader with id `" << vertexShader
              << "`compilation status `" << m_VertexCompilationInfo->GetCompileStatus()
              << "` log:\n" << m_VertexCompilationInfo->GetCompileLog() << std::endl;

    std::cout << "Fragment shader with id `" << fragmentShader
              << "`compilation status: `" << m_FragmentCompilationInfo->GetCompileStatus()
              << "` log:\n" << m_FragmentCompilationInfo->GetCompileLog() << std::endl;

    this->ID = CreateProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    this->Disable();
}

void Shader::Enable()
{
    glUseProgram(this->ID);
}

void Shader::Disable()
{
    glDeleteProgram(this->ID);
}

GLuint Shader::RegisterShader(const GLchar* shaderSource, const GLenum type)
{
    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);

    return shaderID;
}

GLuint Shader::CreateProgram(const GLuint vtxID, const GLuint fragID)
{
    GLuint prg = glCreateProgram();
    glAttachShader(prg, vtxID);
    glAttachShader(prg, fragID);
    glLinkProgram(prg);

    return prg;
}
