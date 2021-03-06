/**
 * @author YC XIANG.
 * @date 01/28, 2022
 */

#ifndef LEARNOPENGL_TEXTURE_H
#define LEARNOPENGL_TEXTURE_H

#include <string>

namespace HelloWorld
{
    class Texture
    {
    public:
        explicit Texture(const std::string& texture_name);

    public:
        unsigned int ID_;
    };
}


#endif //LEARNOPENGL_TEXTURE_H
