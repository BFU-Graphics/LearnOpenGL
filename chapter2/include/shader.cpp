#include "shader.h"

Shader::Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path)
{
    std::string vertex_shader_code = read_file(vertex_shader_path);
    std::string fragment_shader_code = read_file(fragment_shader_path);
    const char *vertex_shader_source = vertex_shader_code.c_str();
    const char *fragment_shader_source = fragment_shader_code.c_str();

    // 编译Vertex Shader
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader_id);

    // 编译Fragment Shader
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader_id);

    // 创建Shader Program
    unsigned int shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, fragment_shader_id);
    glLinkProgram(shader_program_id);

    // 检查上面三个编译是否成功
    check_compile_errors(vertex_shader_id, "VERTEX");
    check_compile_errors(fragment_shader_id, "FRAGMENT");
    check_compile_errors(shader_program_id, "PROGRAM");

    // 为了节省显存，我们可以在这里删除Shader，因为它们已经被链接到了Shader Program中了。
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    ID = shader_program_id;
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
}

void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::check_compile_errors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
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

auto Shader::read_file(const std::string &file_path) -> std::string
{
    std::ifstream file_stream(file_path);
    std::string file_content((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
    return file_content;
}
