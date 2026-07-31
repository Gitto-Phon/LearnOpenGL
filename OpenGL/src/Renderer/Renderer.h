#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <map>

class Scene;
class Shader;
class Vertexs;

// forward declarations for render passes
class StencilPass;
class ModelPass;
class LightPass;
class AlphaPass;

// ===================================================
// Renderer - 将渲染循环拆解为标准的渲染步骤
//   - StencilPass  -> 模板测试描边
//   - ModelPass    -> 3D模型渲染
//   - LightPass    -> 灯光立方体
//   - AlphaPass    -> AlphaTest + AlphaBlend
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
