#pragma once

// ===================================================
// Mesh - 网格类（Assimp 子网格）
// 封装来自 mesh.h 的 Mesh 类
// ===================================================

#include <vector>
#include <string>
#include "Resource/Shader.h"

//定义顶点数据结构体（包含顶点位置，法线，uv坐标）
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

//定义贴图数据结构体（贴图id，贴图类型）
struct Texture {
    unsigned int id = 0;
    std::string type;
    std::string path;//储存纹理路径与其他纹理对比
};

//定义网格数据类
class Mesh {
public:
    //网格数据
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    //构造函数（将所有必须的数据赋予网格）
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,std::vector<Texture> textures) {
        this->vertices = vertices;//Mesh的形参赋予公有变量
        this->indices = indices;
        this->textures = textures;
        //初始化缓冲（VAO,VBO,VEO）
        setupMesh();
    }
    //绘制网格
    void Draw(Shader shader) {
        unsigned int diffuseNr = 1;//漫反射贴图数
        unsigned int specularNr = 1;//镜面反射贴图数
        for (unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);//在绑定之前激活相应的纹理单元
            //获取纹理序号（diffuse_textureN中的N）
            std::string number;
            std::string name = textures[i].type;//获取贴图类型
            //确定贴图数量，将N拼接到纹理类型后，获取对应的uniform名称
            if (name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
            }
            else if (name == "texture_specular") {
                number = std::to_string(specularNr++);
            }
            //设置采样器的位置值为当前激活的纹理单元
            shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);//绑定当前纹理
        }
        glActiveTexture(GL_TEXTURE0);

        //绘制网格
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    //清理缓存
    void deleteBuffer()const
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
private:
    //渲染数据
    unsigned int VAO, VBO, EBO;
    //初始化函数
    void setupMesh() {
        //创建顶点数组对象(VAO)//顶点缓冲对象(VBO)//元素（索引）缓冲对象(EBO)
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);//ID索引//一旦创建缓冲区后,就要选择那个缓冲区(绑定)

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //把用户定义的数据复制到显存缓冲区的函数
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        //vertices.size() * sizeof(Vertex)应该是32个字节，8个float * 每个4字节
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        //Position
        glEnableVertexAttribArray(0);//启用顶点属性
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        //Normal
        glEnableVertexAttribArray(1);
        //offsetof(s,m)，第一个是结构体，第二个参数是这个结构体中的变量名，这个宏会返回该变量距结构体头部的字节偏移量
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        //TexCoords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};