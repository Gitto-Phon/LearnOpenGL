#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Vertexs
{
public:
    //顶点数组， 顶点数组大小， 索引（面ID）数组， 索引（面ID）数组大小, 属性长度数组， 属性数组大小
    Vertexs(float vertices[],int verSize, unsigned int indices[], int indSize, unsigned int prop[], int propSize)
    {
        //创建顶点数组对象(VAO)//顶点缓冲对象(VBO)//元素（索引）缓冲对象(EBO)
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);//ID索引//一旦创建缓冲区后,就要选择那个缓冲区(绑定)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //把用户定义的数据复制到显存缓冲区的函数
        glBufferData(GL_ARRAY_BUFFER, verSize, vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices, GL_STATIC_DRAW);
        setProperty(prop, propSize);
    }
    Vertexs(float vertices[], int verSize, unsigned int prop[], int propSize)
    {
        //创建顶点数组对象(VAO)//顶点缓冲对象(VBO)//元素（索引）缓冲对象(EBO)
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);//ID索引//一旦创建缓冲区后,就要选择那个缓冲区(绑定)
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //把用户定义的数据复制到显存缓冲区的函数
        glBufferData(GL_ARRAY_BUFFER, verSize, vertices, GL_STATIC_DRAW);
        setProperty(prop, propSize);
        //glBindVertexArray(0);
    }
    //设置顶点属性指针
    //属性长度数组， 属性数组大小
    void setProperty(unsigned int prop[], int propSize)
    {
        int vSize = 0;
        int posiP = 0;
        for (int j = 0; j < propSize; j++)  vSize += prop[j];
        for (int i = 0; i < propSize; i++)
        {
            if (i > 0)  posiP += prop[i - 1];
            glVertexAttribPointer(i, prop[i], GL_FLOAT, GL_FALSE, vSize * sizeof(float), (void*)(posiP * sizeof(float)));
            glEnableVertexAttribArray(i);//启用顶点属性
        }
    }
    //绑定VAO
    void useVAO()const
    {
        glBindVertexArray(VAO);
    }

    //清理缓存
    void deleteBuffer()const
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
private:
    unsigned int EBO;
    unsigned int VAO, VBO;
};