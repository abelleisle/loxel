#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>

#include <GL/glew.h>

class Shader
{
    private:
        std::string readShader(const char*); 
        GLuint createShader(const char*, GLenum);

        GLuint program;
        std::unordered_map<std::string, GLuint> attributes;
        std::unordered_map<std::string, GLuint> uniforms;
    public:
        GLuint createProgram(std::string, std::string); 

        GLint addAttribute(std::string);
        GLint addUniform(std::string);

        GLint getAttribute(std::string);
        GLint getUniform(std::string);

        GLuint getProgram();
};

#endif // SHADER_HPP
