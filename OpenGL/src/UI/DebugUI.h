#pragma once

// ===================================================
// 【Step04】DebugUI - ImGui 调试面板
// 职责：每帧绘制 ImGui 调试窗口，用于运行时调整参数
//       被 Application::RenderImGui() 调用
// 包含面板：
//   Step04.1  "Learn OpenGL" 主面板  ← 背景色、灯光颜色
//   Step04.2  "模型" 面板            ← 模型位置/缩放/旋转
//   Step04.3  "灯光" 面板            ← 光源参数
// 静态类，无需实例化
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