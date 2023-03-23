#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string &texture_path)
{
    unsigned int texture_ID;
    glGenTextures(1, &texture_ID);

    glBindTexture(GL_TEXTURE_2D, texture_ID);
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nr_channels;
    //stbi_set_flip_vertically_on_load(true);
    /// 就是个离谱事，这个草不走寻常路，这个草有这句反而是倒过来的，不过还好这次用到的其他材质都不需要反转过来，最好我们自己把草那个图片处理一下（？
    unsigned char *data = stbi_load(texture_path.c_str(), &width, &height, &nr_channels, 0);
    if (data)
    {
        GLenum format;
        if (nr_channels == 1)
            format = GL_RED;
        else if (nr_channels == 3)
            format = GL_RGB;
        else if (nr_channels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        /// 这次才发现这有一个小错误之前忘记把第一个format出现的位置也改成format了，原来是GL_RGB，所以也没有A通道
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        /// 使用GL_CLAMP_TO_EDGE来防止半透明边框。
        /// 如果不这么写会出现一个细细的白色边框
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

    } else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ID = texture_ID;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::Texture() {

}
