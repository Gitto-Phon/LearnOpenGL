#pragma once

#include <glm/glm.hpp>
#include "Renderer/RenderPass.h"

class Shader;
class Vertexs;

// ===================================================
// 【Step03.4】LightPass - 灯光立方体渲染通道
// 职责：绘制点光源方块（可视化光源位置）
//       被 Renderer::Render() 调用（当前注释状态）
// 执行：
//   Step03.4  对每个点光源位置，绘制一个小立方体
// 依赖：
//   着色器：shader_LightMesh（lightMeshVS + lightMeshFS）
//   几何体：cubeV（立方体）
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
