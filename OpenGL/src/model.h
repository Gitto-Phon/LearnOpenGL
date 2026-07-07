#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "mesh.h"
#include "../image/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//定义模型数据类
class Model {
public:
    //文件路径，gamma//加载模型
    Model(std::string const &path, bool gamma = false) 
    {
        loadModel(path);
    }
    //逐个调用每个网格的绘制函数
    void Draw(Shader &shader) {
        for (unsigned int i = 0; i < meshes.size(); i++) {
            meshes[i].Draw(shader);
        }
    }
private:
    //模型数据
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
    //函数
    //加载模型
    void loadModel(std::string path) {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        //aiProcess_Triangulate设置可以将模型全部转换成三角形
        //aiProcess_FlipUVs设置可以在处理的时候翻转y轴的纹理坐标

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }
    //输入参数（根节点，场景节点）//递归函数
    void processNode(aiNode* node, const aiScene* scene) {
        //处理节点所有的网格
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        //对它的子节点重复这一过程
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }
    Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;       //网格顶点属性
        std::vector<Texture> textures;      //贴图
        std::vector<unsigned int> indices;  //顶点索引
        //处理索引
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            //处理顶点位置，法线，纹理坐标
            glm::vec3 vector;
            //顶点位置
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            //法线
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
            //纹理坐标
            if (mesh->mTextureCoords[0]) //网格是否有纹理坐标
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);//将数据填充到vertices尾部
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];//每个面代表一个图元（三角形）//包含多个索引
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);//将索引数据填充到indices尾部
            }
        }
        //处理材质
        if (mesh->mMaterialIndex >= 0) //检查是否包含材质
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];//从场景的mMaterials数组中获取aiMaterial对象
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            //材质对象内部对每种纹理类型都存储了一个纹理位置数组，以aiTextureType_为前缀进行区分
            //loadMaterialTextures函数遍历了给定纹理类型的所有纹理位置，获取了纹理的文件位置，并加载并和生成了纹理，将信息储存在了一个Vertex结构体中。
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }
    //链接纹理数据//此工具函数是从材质中获取纹理
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        //使用GetTextureCount函数检查储存在材质中的纹理数量，需要一个纹理类型参数
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
                aiString str;
                //获取每个纹理的文件位置，将结果储存在一个aiString中
                mat->GetTexture(type, i, &str);
                bool skip = false;
                for (unsigned int j = 0; j < textures_loaded.size(); j++)
                {
                    if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                    {
                        textures.push_back(textures_loaded[j]);
                        skip = true;
                        break;
                    }
                }
                if (!skip)//如果纹理还没有被加载，就加载它
                {
                    Texture texture;
                    texture.id = TextureFromFile(str.C_Str(), directory);
                    texture.type = typeName;
                    texture.path = str.C_Str();
                    textures.push_back(texture);
                    textures_loaded.push_back(texture);//添加到已加载的纹理中
                }
        }
        return textures;
    }
    //加载纹理并返回该纹理的ID
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false)
    {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;//声明纹理尺寸，颜色通道数量
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format = GL_RGB;
            if (nrComponents == 1)
            {
                format = GL_RED;
            }
            else if (nrComponents == 3)
            {
                format = GL_RGB;
            }
            else if (nrComponents == 4)
            {
                format = GL_RGBA;
            }


            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            //为当前绑定的纹理对象设置环绕,过滤方式
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//为纹理放大缩小指定过滤方式
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//放大纹理不会使用MipMap
        }
        else {
            std::cout << "Texture failed to load at path: " << path << std::endl;
        }
        stbi_image_free(data);//释放图像内存

        return textureID;
    }
};