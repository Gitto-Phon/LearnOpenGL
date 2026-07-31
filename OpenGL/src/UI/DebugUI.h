#pragma once

// ===================================================
// DebugUI - 控制并绘制 Debug UI 面板
// 封装 ImGui 操作，按钮与滑动条修改场景状态
// 从原 UI.h 的 App::RenderUI 迁移
// ===================================================

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//初始化参数
extern glm::vec3 backGroundColor;//背景颜色

//模型变换
extern glm::vec3 modelPos;
extern glm::vec3 modelScale;

extern glm::vec3 lightPos;      //灯光位置
extern glm::vec3 lightColor;    //灯光颜色
extern float lightRange;        //灯光范围

struct dirLight
{
    glm::vec3 direction = glm::vec3(0.2f, -0.325f, -0.3f);
    glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
};

struct pointLight
{
    glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
    glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};

struct spotLight
{

};

extern dirLight dirLight_0;
extern pointLight pointLight_0;

namespace App
{
    //选中结果
    extern bool isShowDrag;
    //字符串结果
    extern std::string text;
    //拖拽值
    extern float fValue;

    extern bool show_demo_window;
    extern bool show_model_window;
    extern bool show_light_window;
    
    void RenderUI();
}

namespace DebugUI
{
    // 初始化 UI 状态（从原 UI.h 的 App 命名空间变量迁移）
    void Init();

    // 每帧绘制 ImGui 窗口
    void Draw();
}