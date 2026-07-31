#pragma once

#include <glm/glm.hpp>
#include "Renderer/RenderPass.h"

class Shader;
class Vertexs;
class Model;

// ===================================================
// 【Step03.1】ModelPass - 模型+光照渲染通道
// 职责：渲染 3D 模型（立方体 + 灯光方块）
//       被 Renderer::Render() 调用（当前注释状态）
// 执行子步骤：
//   Step03.1a  使用 shader_Model 绘制立方体（带光照计算）
//   Step03.1b  使用 shader_LightMesh 绘制灯光方块
// 依赖：
//   着色器：shader_Model（modelVS + modelFS）、shader_LightMesh（lightMeshVS + lightMeshFS）
//   几何体：cubeV（立方体）
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
