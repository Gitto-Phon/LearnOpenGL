#pragma once

// ===================================================
// Texture - 贴图类
// 封装贴图加载函数 setTexture()
// ===================================================

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"//图片加载

//纹理路径,纹理ID,Y轴翻转,纹理类型
inline unsigned int setTexture(const char* texPath, unsigned int id, bool flip, GLint param)
{
    //生成纹理对象
    unsigned int textureID;
    glGenTextures(1, &textureID);

    //从磁盘中加载图像
    int width, height, nrChannels;//声明纹理尺寸，颜色通道数量
    stbi_set_flip_vertically_on_load(flip);//图像方向
    unsigned char *data = stbi_load(texPath, &width, &height, &nrChannels, 0);//(文件名,宽度,高度,颜色通道的个数)

    if (data)
    {//使用加载的图像生成纹理
        glActiveTexture(33984 + id);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, param, width, height, 0, param, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);


        //为当前绑定的纹理对象设置环绕,过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//为纹理放大缩小指定过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//放大纹理不会使用MipMap
    }
    else
    {
        std::cout << "Failed to load texture" << texPath << std::endl;
    }
    stbi_image_free(data);//释放图像内存

    return textureID;
}