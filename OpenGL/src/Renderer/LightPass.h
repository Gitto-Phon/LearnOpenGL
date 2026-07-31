#pragma once

#include <glm/glm.hpp>
#include "Renderer/RenderPass.h"

class Shader;
class Vertexs;

// ===================================================
// LightPass - 渲染灯光颜色（点光源方块）
// 从原 Application.cpp 的灯光模型渲染代码迁移（当前注释状态）
// ===================================================

class LightPass : public RenderPass
{
public:
    void Execute(
        const glm::mat4& view,
        const glm::mat4& proj,
        Shader& shader_LightMesh,
        Vertexs& cubeV
    );
};
