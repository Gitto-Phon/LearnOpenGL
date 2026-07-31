#pragma once

#include <glm/glm.hpp>
#include "Renderer/RenderPass.h"

// forward declarations
class Shader;
class Vertexs;

// ===================================================
// StencilPass - 渲染需要描边效果的物体
// 从原 Application.cpp 的模板测试渲染代码迁移
// ===================================================

class StencilPass : public RenderPass
{
public:
    void Execute(
        const glm::mat4& view,
        const glm::mat4& proj,
        Shader& shader_StencilTest,
        Shader& shader_Depth,
        Vertexs& planV,
        Vertexs& cubeV,
        unsigned int floorTexture
    );
};
