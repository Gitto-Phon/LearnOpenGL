#pragma once

#include "Renderer/RenderPass.h"

#include <glm/glm.hpp>
#include <vector>
#include <map>

class Shader;
class Vertexs;
class Camera;

// ===================================================
// AlphaPass - 渲染需要AlphaTest和AlphaBlend的片段（植被/窗户）
// 从原 Application.cpp 的 alpha 渲染代码迁移（当前注释状态）
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
