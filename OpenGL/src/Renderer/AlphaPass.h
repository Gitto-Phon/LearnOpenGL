#pragma once

#include "Renderer/RenderPass.h"

#include <glm/glm.hpp>
#include <vector>
#include <map>

class Shader;
class Vertexs;
class Camera;

// ===================================================
// 【Step03.3】AlphaPass - Alpha 混合/透明度渲染通道
// 职责：按距离排序绘制透明窗户（远处→近处）
//       被 Renderer::Render() 调用（当前注释状态）
// 执行：
//   Step03.3  从远到近逐个绘制透明窗户，使用 Alpha 混合
// 依赖：
//   着色器：shader_AlphaTest（alphaVS + alphaFS）
//   几何体：alphaV（窗户顶点）、planV（平面）、cubeV（立方体）
// ===================================================

class AlphaPass : public RenderPass
{
public:
    void Execute(
        const glm::mat4& view,
        const glm::mat4& proj,
        Shader& shader_AlphaTest,
        Vertexs& planV,
        Vertexs& cubeV,
        Vertexs& alphaV,
        unsigned int floorTexture,
        unsigned int alpheTexture,
        const Camera& camera,
        const std::vector<glm::vec3>& windows
    );
};
