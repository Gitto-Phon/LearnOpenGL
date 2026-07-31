#pragma once

#include <glm/glm.hpp>
#include "Renderer/RenderPass.h"
#include "Resource/Shader.h"
#include "Resource/VertexArray.h"

// ===================================================
// 【Step03.2】StencilPass - 模板测试描边渲染通道
// 职责：绘制地板 + 立方体 + 模板描边效果
//       被 Renderer::Render() 调用
// 执行子步骤：
//   Step03.2a  绘制地板（禁用模板写入，模板值保持为 0）
//   Step03.2b  绘制立方体（模板缓冲写入 1，颜色写入）
//   Step03.2c  绘制放大立方体描边（模板值 ≠ 1 才绘制，仅边框）
// 依赖：
//   着色器：shader_StencilTest（stencilVS + lightMeshFS）、shader_Depth（depthVS + depthFS）
//   几何体：planV（平面）、cubeV（立方体）
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
