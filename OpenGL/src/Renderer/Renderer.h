#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <map>

class Scene;

#include "Resource/Shader.h"
#include "Resource/VertexArray.h"

// forward declarations for render passes
class StencilPass;
class ModelPass;
class LightPass;
class AlphaPass;

// ===================================================
// 【Step03】Renderer - 渲染器，编排渲染通道
// 职责：持有 4 个渲染通道子类，按顺序调度执行
//       每帧被 Application::Run() 调用 Render()
// 渲染通道执行顺序：
//   Step03.1  m_modelPass->Execute()    ← 模型+光照渲染（当前注释状态）
//   Step03.2  m_stencilPass->Execute()  ← 地板 + 立方体 + 模板描边
//   Step03.3  m_alphaPass->Execute()    ← Alpha 混合/透明度渲染（当前注释状态）
//   Step03.4  m_lightPass->Execute()    ← 点光源方块渲染（当前注释状态）
// 持有：
//   StencilPass* m_stencilPass  → 模板测试描边
//   ModelPass*   m_modelPass    → 3D 模型渲染
//   LightPass*   m_lightPass    → 灯光立方体
//   AlphaPass*   m_alphaPass    → AlphaTest + AlphaBlend
// ===================================================

class Renderer
{
public:
    Renderer();
    ~Renderer();

    // 每帧调用，按顺序执行所有渲染通道
    // scene: 场景状态（摄像机、帧时间等）
    // shader_StencilTest, shader_Depth: 模板/深度着色器
    // planV, cubeV, alphaV: 顶点对象
    // floorTexture: 地面贴图
    void Render(
        Scene& scene,
        Shader& shader_StencilTest,
        Shader& shader_Depth,
        Shader& shader_Model,
        Shader& shader_LightMesh,
        Shader& shader_AlphaTest,
        Vertexs& planV,
        Vertexs& cubeV,
        Vertexs& alphaV,
        unsigned int floorTexture,
        unsigned int alpheTexture
    );

private:
    StencilPass* m_stencilPass;
    ModelPass*   m_modelPass;
    LightPass*   m_lightPass;
    AlphaPass*   m_alphaPass;
};
