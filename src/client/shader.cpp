#include <client/shader.hpp>

#include <fstream>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

std::string Shader::readShader(const char* filepath)
{
    std::string contents = "";
    std::ifstream file(filepath, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Could not read shader " << filepath << 
            ". Shader doesn't exist" << std::endl;
        return "";
    }

    std::string line = "";
    while (!file.eof()) {
        std::getline(file, line);
        contents.append(line + "\n");
    }

    file.close();
    return contents;
}

GLuint Shader::createShader(const char* filepath, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    std::string shaderStr = readShader(filepath);
    const char* shaderSrc = shaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> shaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);
    std::cout << &shaderError[0] << std::endl;

    return shader;
}

GLuint Shader::createProgram(std::string vertexPath, std::string fragmentPath)
{
    GLuint vertex = createShader(vertexPath.c_str(), GL_VERTEX_SHADER);
    GLuint fragment = createShader(fragmentPath.c_str(), GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    GLint result = GL_FALSE;
    int logLength;

    glGetProgramiv(program, GL_COMPILE_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    this->program = program;

    return program;
}

// TODO exceptions
GLint Shader::addAttribute(std::string attrib)
{
    GLint attribute = glGetAttribLocation(program, attrib.c_str());

    if (attribute == -1)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                "Could not bind attribute %s", attrib.c_str());

    attributes.emplace(attrib, attribute);
    return attribute;
}

GLint Shader::addUniform(std::string unfi)
{
    GLint uniform = glGetUniformLocation(program, unfi.c_str());

    if (uniform == -1)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                "Could not bind uniform %s", unfi.c_str());

    uniforms.emplace(unfi, uniform);
    return uniform;
}

// TODO exceptions
GLint Shader::getAttribute(std::string attrib)
{
    return attributes.at(attrib);
}

GLint Shader::getUniform(std::string unfi)
{
    return uniforms.at(unfi);
}

GLuint Shader::getProgram()
{
    return program;
}
