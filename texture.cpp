#include "texture.h"

Texture::Texture(const char* resourcePath, GLenum type, GLenum slot, GLenum format, GLenum pixelType)
{
    initializeOpenGLFunctions();

    m_ResourcePath = resourcePath;
    m_Type = type;

    QImage* img = new QImage(resourcePath);

    // Generates an OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(m_Type, ID);

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(m_Type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(m_Type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_Type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(m_Type, 0, GL_RGBA, img->width(), img->height(), 0, format, pixelType, img->bits());
    // Generates MipMaps
    glGenerateMipmap(m_Type);

    delete img;

    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(m_Type, 0);
}

Texture::~Texture()
{
    Delete();
    Unbind();
}

void Texture::AssignTextureUnit(ShaderProgram* program, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(program->ID, uniform);
    // Shader needs to be enabled before changing the value of a uniform
    program->Enable();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glBindTexture(m_Type, ID);
}

void Texture::Unbind()
{
    glBindTexture(m_Type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
