/**
 * @author YC XIANG.
 * @date 01/27, 2022
 */

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <string>

namespace HelloWorld
{
    class Shader
    {
    public:
        Shader(const std::string &vertex_shader_name, const std::string &fragment_shader_name, const std::string &geometry_shader_name = "");
        void use() const;
    public:
        unsigned int ID_;

    private:
        static void check_compile_error(unsigned int shader, const std::string& type);
    };
}

#endif //LEARNOPENGL_SHADER_H
