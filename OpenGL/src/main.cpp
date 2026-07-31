#include "Core/Application.h"

// ===================================================
// 【Step01】程序入口 - main.cpp
// 职责：创建 Application 对象，串联整个程序生命周期
//       窗口初始化 → 资源加载 → 主循环 → 自动清理
// 执行顺序：
//   Step01.1  Application app          ← 构造 Application（注册单例）
//   Step01.2  app.InitWindow()        ← 跳转 Step02 - 创建窗口+OpenGL环境
//   Step01.3  app.InitResources()     ← 跳转 Step02 - 加载着色器/VAO/贴图
//   Step01.4  app.Run()               ← 跳转 Step02 - 进入主渲染循环
//   Step01.5  ~Application()          ← 跳出作用域自动析构，清理所有资源
// ===================================================

int main()
{
    Application app;

    // 窗口初始化（从原 glInit 迁移）
    GLFWwindow* window = app.InitWindow(
        Scene::SCR_WIDTH,
        Scene::SCR_HEIGHT,
        "LearnOpenGL"
    );
    if (!window)
        return -1;

    // 初始化渲染资源（着色器、VAO、贴图）
    app.InitResources();

    // 进入主渲染循环（从原 while 循环迁移）
    app.Run();

    return 0;
}
