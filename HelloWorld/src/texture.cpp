/**
 * @author YC XIANG.
 * @date 01/28, 2022
 */

#include <glad/glad.h>

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

#include <iostream>

using namespace HelloWorld;

Texture::Texture(const std::string &texture_name)
{
    std::string str = std::string(MY_TEXTURE_DIR) + texture_name;

    int width, height, nrChannels;

    unsigned char *data = stbi_load(str.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glGenTextures(1, &ID_);
        glBindTexture(GL_TEXTURE_2D, ID_);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        std::cout << "Failed to load texture:" << texture_name << std::endl;
    }

    stbi_image_free(data);
}
