/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include "shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace HelloWorld;

Shader::Shader(const std::string &vertex_shader_name, const std::string &fragment_shader_name, const std::string &geometry_shader_name)
{
    unsigned int vertex, fragment;

    /* VERTEX SHADER */
    {
        std::ifstream     ins;
        std::stringstream ss;

        // Open Shader File and Redirect Buffer(Shader Source) into StringStream
        ins.open(std::string(MY_SHADER_DIR) + vertex_shader_name);
        ss << ins.rdbuf();

        // Compile Vertex Shader
        std::string str          = ss.str();
        const char  *vertex_code = str.c_str();
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code, NULL);
        glCompileShader(vertex);
        check_compile_error(vertex, "VERTEX");

        ins.close();
        ss.clear();
    }

    /* FRAGMENT SHADER */
    {
        std::ifstream     ins;
        std::stringstream ss;

        // Open Shader File and Redirect Buffer(Shader Source) into StringStream
        ins.open(std::string(MY_SHADER_DIR) + fragment_shader_name);
        ss << ins.rdbuf();

        // Compile Fragment Shader
        std::string str            = ss.str();
        const char  *fragment_code = str.c_str();
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code, NULL);
        glCompileShader(fragment);
        check_compile_error(fragment, "FRAGMENT");

        ins.close();
        ss.clear();
    }

    ID_ = glCreateProgram();
    glAttachShader(ID_, vertex);
    glAttachShader(ID_, fragment);
    glLinkProgram(ID_);
    check_compile_error(ID_, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(ID_);
}

void Shader::check_compile_error(unsigned int shader, const std::string &type)
{
    GLint  success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
