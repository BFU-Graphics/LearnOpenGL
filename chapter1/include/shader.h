#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

class Shader
{
public:
    unsigned int ID;

public:
    Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
    void use() const;
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;

private:
    static void check_compile_errors(unsigned int shader, std::string type);
    static auto read_file(const std::string &file_path) -> std::string;
};

#endif //LEARNOPENGL_SHADER_H
