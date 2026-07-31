#pragma once

#include <glm/glm.hpp>
#include "Camera.h"

// ===================================================
// Scene - 存储场景状态（相机、帧时间、背景色等）
// 从原 Application.cpp/h 迁移
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
