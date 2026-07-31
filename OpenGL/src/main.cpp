#include "Core/Application.h"

// ===================================================
// main - 程序入口
// 从原 Application.cpp 的 main() 迁移
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
