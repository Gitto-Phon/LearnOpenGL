#pragma once

#include <glm/glm.hpp>
#include "Renderer/RenderPass.h"

class Shader;
class Vertexs;
class Model;

// ===================================================
// ModelPass - 渲染3D模型的主光源与材质
// 从原 Application.cpp 的 model/Light 部分迁移（当前注释状态）
// ===================================================

class ModelPass : public RenderPass
{
public:
    void Execute(
        const glm::mat4& view,
        const glm::mat4& proj,
        Shader& shader_Model,
        Shader& shader_LightMesh,
        Vertexs& cubeV,
        Model* model = nullptr
    );
};
