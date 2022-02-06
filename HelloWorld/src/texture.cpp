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
        if(texture_name=="container.jpg")
        {
            glGenTextures(1, &ID_1);
            glBindTexture(GL_TEXTURE_2D, ID_1);
            // set the texture wrapping parameters
            //使用glTexParameter*函数对单独的一个坐标轴设置（s、t（如果是使用3D纹理那么还有一个r）它们和x、y、z是等价的）
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            //进行放大(Magnify)和缩小(Minify)操作的时候可以设置纹理过滤的选项，比如你可以在纹理被缩小的时候使用邻近过滤，被放大时使用线性过滤。
            //这里放大缩小都是线性过滤
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_set_flip_vertically_on_load(true);
            //最小过滤选项的最后一个参数，若为放大过滤选项则无用
            //因为多级渐远纹理主要是使用在纹理被缩小的情况下的：纹理放大不会使用多级渐远纹理，
            //为放大过滤设置多级渐远纹理的选项会产生一个GL_INVALID_ENUM错误代码。
            //GL_NEAREST_MIPMAP_NEAREST	使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
            //GL_LINEAR_MIPMAP_NEAREST	使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
            //GL_NEAREST_MIPMAP_LINEAR	在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
            //GL_LINEAR_MIPMAP_LINEAR	在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);//多级渐远纹理
        }else if(texture_name=="awesomeface.png"){
            glGenTextures(1, &ID_);
            glBindTexture(GL_TEXTURE_2D, ID_);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_set_flip_vertically_on_load(true);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);//多级渐远纹理
        }

    } else
    {
        std::cout << "Failed to load texture:" << texture_name << std::endl;
    }

    stbi_image_free(data);//释放图像的内存
}
