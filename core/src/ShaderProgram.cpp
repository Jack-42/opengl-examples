#include "core/gl/ShaderProgram.hpp"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

static unsigned int compileShader(unsigned int type, const std::string &source);
static unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader);

ShaderProgram::ShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    m_id = linkProgram(vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

void ShaderProgram::bind() const
{
    glUseProgram(m_id);
}

void ShaderProgram::unbind() const
{
    glUseProgram(0);
}

int ShaderProgram::getAttribLocation(const std::string& name) const
{
    return glGetAttribLocation(m_id, name.c_str());
}

static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    // check for compile errors
    int isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
        // get error message
        int maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLogData(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLogData[0]);
        std::string infoLog(std::begin(infoLogData), std::end(infoLogData));

        // clean up
        glDeleteShader(shader);

        std::string typeStr = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
        std::string errorMessage = "Failed to compile " + typeStr + " shader!\n" + infoLog;

        throw std::runtime_error(errorMessage);
    }

    return shader;
}

static unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // check for link errors
    int isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        // get error message
        int maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLogData(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLogData[0]);
        std::string infoLog(std::begin(infoLogData), std::end(infoLogData));

        // clean up
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        std::string errorMessage = "Failed to link shader program!\n" + infoLog;

        throw std::runtime_error(errorMessage);
    }

    // clean up, do not need temporary compile results
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
