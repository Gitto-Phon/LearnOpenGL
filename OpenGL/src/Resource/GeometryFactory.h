#pragma once

#include <glm/glm.hpp>
#include <vector>

// ===================================================
// GeometryFactory - 提供硬编码顶点数据
// 从原 Application.h 迁移
// ===================================================

namespace Resource
{

// 顶点数据 -------------- Vertex Data ---------------
// 带法线贴图UV的立方体顶点 (8 属性: pos3 + normal3 + tex2)
extern float vertices[];
extern const int verticesSize;

// 立方体索引
extern unsigned int indices[];
extern const int indicesSize;

// 顶点属性长度数组 [pos3, normal3, tex2] = [3, 3, 2]
extern unsigned int idex[];
extern unsigned int idexSize;

// 简版顶点属性长度 [pos3, tex2] = [3, 2]
extern unsigned int idexs[];

// 简版立方体 (5 属性: pos3 + tex2)
extern float cubeVertices[];
extern const int cubeVerticesSize;

// 平面顶点 (5 属性: pos3 + tex2)
extern float planeVertices[];
extern const int planeVerticesSize;

// Alpha混合面片 (四边形, 5 属性: pos3 + tex2)
extern float alphaVertices[];
extern const int alphaVerticesSize;

// 方盒位置数组
extern glm::vec3 cubePositions[];
extern const int cubePositionsCount;

// 点光源位置
extern glm::vec3 pointlightPositions[];
extern const int pointlightCount;

// 窗户位置（Alpha混合）
extern std::vector<glm::vec3> windows;

} // namespace Resource
