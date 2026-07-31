#pragma once

#include <glm/glm.hpp>
#include "Camera.h"

// ===================================================
// [数据模块] Scene - 场景状态容器
// 职责：持有场景级别的运行时数据，被 Application 和 Renderer 共同访问
// 持有：
//   Camera camera       → 摄像机（位置/视角/投影矩阵）
//   backGroundColor     → 背景色（可由 DebugUI 动态修改）
//   deltaTime / lastFrame → 帧时间（用于摄像机平滑移动）
// ===================================================

class Scene
{
public:
    Camera camera;                              // 摄像机类对象

    glm::vec3 backGroundColor = glm::vec3(0.1f, 0.1f, 0.1f); // 背景颜色

    static const unsigned int SCR_WIDTH  = 1920; // 默认屏幕宽度
    static const unsigned int SCR_HEIGHT = 1080;  // 默认屏幕高度

    // 帧时间
    float deltaTime = 0.0f;     // 两帧之间时间差
    float lastFrame = 0.0f;     // 上一帧的时间
};
