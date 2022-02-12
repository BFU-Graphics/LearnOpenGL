/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#include "shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace HelloModel;

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

void Shader::set_bool(const std::string &name, bool value) const
{
    this->use();
    glUniform1i(glGetUniformLocation(ID_, name.c_str()), (int) value);
}

void Shader::set_int(const std::string &name, int value) const
{
    this->use();
    glUniform1i(glGetUniformLocation(ID_, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
    this->use();
    glUniform1f(glGetUniformLocation(ID_, name.c_str()), value);
}

void Shader::set_vec2(const std::string &name, const glm::vec2 &value) const
{
    this->use();
    glUniform2fv(glGetUniformLocation(ID_, name.c_str()), 1, &value[0]);
}

void Shader::set_vec2(const std::string &name, float x, float y) const
{
    this->use();
    glUniform2f(glGetUniformLocation(ID_, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    this->use();
    glUniform3fv(glGetUniformLocation(ID_, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string &name, float x, float y, float z) const
{
    this->use();
    glUniform3f(glGetUniformLocation(ID_, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    this->use();
    glUniform4fv(glGetUniformLocation(ID_, name.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const std::string &name, float x, float y, float z, float w)
{
    this->use();
    glUniform4f(glGetUniformLocation(ID_, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string &name, const glm::mat2 &mat) const
{
    this->use();
    glUniformMatrix2fv(glGetUniformLocation(ID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat3(const std::string &name, const glm::mat3 &mat) const
{
    this->use();
    glUniformMatrix3fv(glGetUniformLocation(ID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat4(const std::string &name, const glm::mat4 &mat) const
{
    this->use();
    glUniformMatrix4fv(glGetUniformLocation(ID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_texture(const std::string &texture_name, int texture_ID) const
{
    this->use();
    glUniform1i(glGetUniformLocation(ID_, texture_name.c_str()), texture_ID);
}
