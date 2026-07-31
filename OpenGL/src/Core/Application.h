#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene/Scene.h"
#include "Renderer/Renderer.h"
#include "Resource/Shader.h"
#include "Resource/VertexArray.h"

// ===================================================
// 【Step02】应用程序主类 - Application.h
// 职责：管理窗口创建、资源加载、渲染循环、资源清理
//       是 main() 和所有子模块之间的桥梁
// 公开接口（按调用顺序）：
//   Step02.1  InitWindow()       ← 创建 GLFW 窗口 + GLAD + OpenGL 状态 + ImGui
//   Step02.2  InitResources()    ← 编译着色器 + 创建 VAO + 加载贴图 + 初始化 UI
//   Step02.3  Run()              ← 主渲染循环（每帧：输入→渲染→UI→交换缓冲）
//   Step02.4  ~Application()     ← 析构时自动调用 CleanupResources()
// 持有组件：
//   Scene scene       → 场景状态（摄像机、帧时间、背景色）
//   Renderer renderer → 渲染器（编排 4 个渲染通道）
// ===================================================

class Application
{
public:
    Application();
    ~Application();

    // 初始化窗口和OpenGL环境（从 glInit 迁移）
    // 返回 nullptr 表示初始化失败
    GLFWwindow* InitWindow(int screenWidth, int screenHeight, const char* title);

    // 初始化渲染资源（着色器、VAO、贴图）
    void InitResources();

    // 运行主循环（从 main() 迁移）
    void Run();

    // 获取场景状态
    Scene& GetScene() { return scene; }

private:
    // ---------- GLFW 回调函数（静态）----------
    // 窗口大小变化回调
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    // 鼠标移动回调
    static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    // 鼠标滚轮回调
    static void ScrollCallback(GLFWwindow* window, double xposIn, double yposIn);

    // 单例指针（供静态回调函数访问）
    static Application* s_instance;

    // ---------- 窗口 ----------
    GLFWwindow* window = nullptr;

    // ---------- 核心组件 ----------
    Scene    scene;     // 场景状态（摄像机、帧时间等）
    Renderer renderer;  // 渲染器

    // ---------- 着色器 ----------
    Shader* shader_Model       = nullptr; // 模型着色器
    Shader* shader_Light       = nullptr; // 灯光着色器
    Shader* shader_LightMesh   = nullptr; // 灯光模型着色器
    Shader* shader_Depth       = nullptr; // 深度模型着色器
    Shader* shader_StencilTest = nullptr; // 模板测试着色器
    Shader* shader_AlphaTest   = nullptr; // Alpha测试着色器
    Shader* shader_RenderTarget = nullptr; // 帧缓冲着色器

    // ---------- 顶点对象 ----------
    Vertexs* cubeV  = nullptr;
    Vertexs* planV  = nullptr;
    Vertexs* alphaV = nullptr;

    // ---------- 贴图 ----------
    unsigned int cubeTexture  = 0;
    unsigned int floorTexture = 0;
    unsigned int alpheTexture = 0;

    // ---------- 内部辅助方法 ----------
    void InitImGui(GLFWwindow* window);  // 初始化 ImGui
    void RenderImGui();                  // 每帧渲染 ImGui
    void CleanupResources();             // 清理资源
};
