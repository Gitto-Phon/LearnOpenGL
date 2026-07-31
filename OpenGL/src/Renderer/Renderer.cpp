#include "Renderer.h"

#include <glad/glad.h>

#include "Scene/Scene.h"
#include "Resource/GeometryFactory.h"
#include "Renderer/StencilPass.h"
#include "Renderer/ModelPass.h"
#include "Renderer/LightPass.h"
#include "Renderer/AlphaPass.h"
#include "Shader/shader.h"
#include "Resource/VertexArray.h"
#include "Scene/Camera.h"

Renderer::Renderer()
    : m_stencilPass(new StencilPass())
    , m_modelPass(new ModelPass())
    , m_lightPass(new LightPass())
    , m_alphaPass(new AlphaPass())
{
}

Renderer::~Renderer()
{
    delete m_stencilPass;
    delete m_modelPass;
    delete m_lightPass;
    delete m_alphaPass;
}

void Renderer::Render(
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
)
{
    // 初始化
    glClearColor(
        scene.backGroundColor.x,
        scene.backGroundColor.y,
        scene.backGroundColor.z, 1.0f);           // 设置清空屏幕所用的颜色//状态设置函数

    // 清空屏幕（缓冲位：BUFFER_BIT 可用的有GL_COLOR_...  GL_DEPTH_...  GL_STENCIL_...）
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // 清除前一帧的颜色缓冲和深度缓冲//状态使用函数
    // 开启了深度测试和模板测试，需要在每帧前清除缓冲，也就是更新缓冲

    // 初始化MVP矩阵
    glm::mat4 model = glm::mat4(1.0f);             // 初始化模型矩阵
    glm::mat4 view  = scene.camera.getViewMat();   // 初始化观察矩阵
    glm::mat4 proj  = scene.camera.getProjectionMat(); // 初始化透视矩阵

    // STL库的map数据结构，会自动根据键值对它的值排序(这里的键值是每个窗户对应的距离)
    std::map<float, glm::vec3> sorted;
    for (unsigned int i = 0; i < Resource::windows.size(); i++)
    {
        float distance = glm::length(scene.camera.cameraPos - Resource::windows[i]);
        sorted[distance] = Resource::windows[i];   // 每个窗户给存一个距离键值，按低到高排序
    }

    // ==================== 渲染通道 ====================

    //------------ model ---------------
    // 模型+光照渲染（当前注释状态）
    m_modelPass->Execute(view, proj, shader_Model, shader_LightMesh, cubeV, nullptr);

    //------------ stencil 模板测试 ------------
    {
        m_stencilPass->Execute(view, proj, shader_StencilTest, shader_Depth, planV, cubeV, floorTexture);
    }

    //------------ alpha ------------
    // Alpha混合渲染（当前注释状态）
    //m_alphaPass->Execute(view, proj, shader_AlphaTest, planV, cubeV, alphaV, floorTexture, alpheTexture, scene.camera, Resource::windows);

    //------------ light ------------
    // 灯光立方体渲染（当前注释状态）
    //m_lightPass->Execute(view, proj, shader_LightMesh, cubeV);
}
