#include "shader.h"

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
ShaderProgram::ShaderProgram()
{
    Q_INIT_RESOURCE(resources);
    initializeOpenGLFunctions();

    // Read shader files
    m_VertexShaderSource = ReadShaderFile(":/Shaders/vertex.shader");
    m_FragmentShaderSource = ReadShaderFile(":/Shaders/fragment.shader");

    // Register shaders
    GLuint vertexShader = RegisterShader(m_VertexShaderSource.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = RegisterShader(m_FragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);

    // Retreive shader compilation logs
    m_VertexCompilationInfo = new ShaderCompilationInfo(vertexShader);
    m_FragmentCompilationInfo = new ShaderCompilationInfo(fragmentShader);

    // Print shader compilation logs
    std::string vertexCompileLog = "Vertex shader compilation status " + std::to_string(m_VertexCompilationInfo->GetCompileStatus());

    if(m_VertexCompilationInfo->GetCompileStatus() != GL_TRUE)
        vertexCompileLog += " log:\n" + m_VertexCompilationInfo->GetCompileLog();

    std::string fragmentCompileLog = "Fragment shader compilation status " + std::to_string(m_FragmentCompilationInfo->GetCompileStatus());

    if(m_FragmentCompilationInfo->GetCompileStatus() != GL_TRUE)
        fragmentCompileLog += " log:\n" + m_FragmentCompilationInfo->GetCompileLog();

    std::cout << vertexCompileLog << std::endl;
    std::cout << fragmentCompileLog << std::endl;

    this->ID = CreateProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    this->Disable();
}

void ShaderProgram::Enable()
{
    glUseProgram(this->ID);
}

void ShaderProgram::Disable()
{
    glDeleteProgram(this->ID);
}

const std::string ShaderProgram::ReadShaderFile(const QString resourcePath) const
{
    QFile shaderFile(resourcePath);

    if (!shaderFile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw("Shader file \"" + resourcePath + "\" could not be loaded");

    std::string content;

    while (!shaderFile.atEnd()) {
        content += shaderFile.readLine().constData();
    }

    return content;
}

GLuint ShaderProgram::RegisterShader(const GLchar* shaderSource, const GLenum type)
{
    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);

    return shaderID;
}

GLuint ShaderProgram::CreateProgram(const GLuint vtxID, const GLuint fragID)
{
    GLuint prg = glCreateProgram();
    glAttachShader(prg, vtxID);
    glAttachShader(prg, fragID);
    glLinkProgram(prg);

    return prg;
}

const ShaderCompilationInfo* ShaderProgram::GetVertexShaderCompilation() const
{
    return m_VertexCompilationInfo;
}

const ShaderCompilationInfo* ShaderProgram::GetFragmentShaderCompilation() const
{
    return m_FragmentCompilationInfo;
}
