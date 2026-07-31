#include "Application.h"

#include <iostream>

// ImGui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// 资源
#include "Resource/GeometryFactory.h"
#include "Resource/Texture.h"         // setTexture / TextureFromFile

// UI
#include "UI/DebugUI.h"

// ===================================================
// 静态成员
// ===================================================
Application* Application::s_instance = nullptr;

// ===================================================
// 构造 / 析构
// ===================================================
Application::Application()
{
    s_instance = this;
}

Application::~Application()
{
    CleanupResources();
    s_instance = nullptr;
}

// ===================================================
// GLFW 回调函数（静态）
// ===================================================
// 窗口大小变化 — framebuffer_size_callback
void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height); // 前两个控制左下角,后两个右上角(像素)
}

// 鼠标监听 — mouse_callback
void Application::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (s_instance)
    {
        s_instance->scene.camera.mouse_callback(xposIn, yposIn);
    }
}

// 鼠标滚轮 — scroll_callback（改变fov）
void Application::ScrollCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (s_instance)
    {
        s_instance->scene.camera.scroll_callback(yposIn);
    }
}

// ===================================================
// 创建渲染窗口（从原 Application.h 的 glInit 函数迁移）
// ===================================================
GLFWwindow* Application::InitWindow(int screenWidth, int screenHeight, const char* title)
{
    // 实例化GLFW窗口
    glfwInit(); // 初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 版本号:4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式:Core-profile

    // 创建窗口对象   设置窗口大小,标题，窗口模式
    GLFWwindow* w = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
    // 全屏函数glfwGetPrimaryMonitor()
    if (w == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // 释放资源
        return nullptr;
    }
    glfwMakeContextCurrent(w); // 设置当前环境为当前窗口的OpenGL环境

    glfwSetFramebufferSizeCallback(w, FramebufferSizeCallback); // 设置回调函数改变视口大小
    glfwSetCursorPosCallback(w, MouseCallback);                 // 光标回调函数
    glfwSetScrollCallback(w, ScrollCallback);                   // 滚轮回调函数

    // 光标捕捉（Capture）
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);    // 正常模式
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);    // 隐藏光标
    glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);        // 禁用和捕捉光标

    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    //stbi_set_flip_vertically_on_load(true); // 翻转y轴(texture)

    glEnable(GL_DEPTH_TEST); // 开启深度测试
    //glDepthMask(GL_FALSE); // 禁用深度缓冲写入
    //glDepthFunc(GL_ALWAYS); // 设置深度缓冲通过条件

    glEnable(GL_STENCIL_TEST); // 开启模板测试
    //glStencilMask(0xFF); // 开启模板缓冲写入（写入时保持原样）
    //glStencilMask(0x00); // 禁用模板缓冲写入（写入时变成0）

    //glStencilOp(模板未通过的行为, 模板通过(深度未通过)的行为, 模板与深度都通过)
    //REPLACE是设置成glStencilFunc的参考值
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // 设置每一帧模板测试的行为
    //REPLACE--模板值设置为glStencilFunc函数设置的参考值

    //glEnable(GL_CULL_FACE); // 开启面剔除
    //glCullFace(GL_BACK); // 默认值为BACK，只剔除背向面，还有GL_FRONT以及GL_FRONT_AND_BACK
    //glFrontFace(GL_CCW); // 默认值为CCW，定义逆时针环绕顺序为三角形正面，还有CW，效果相反

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //第一个参数是应用到所有三角形的正面和背面,第二个参数是用线绘制,设回默认是GL_FILL

    // 初始化 ImGui
    InitImGui(w);

    window = w;
    return w;
}

// ===================================================
// 初始化 ImGui
// ===================================================
void Application::InitImGui(GLFWwindow* window)
{
    //------------------------------------imgui-------------------------------
    // Setup Dear ImGui context//设置imgui上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls启用键盘控制

    // 主题颜色
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    //安装glfw回调函数并链接到现有的回调函数
    ImGui_ImplOpenGL3_Init("#version 460");

    // 设置微软雅黑字体，以及字体大小
    ImFont* font = io.Fonts->AddFontFromFileTTF
    (
        "C:/Windows/Fonts/msyh.ttc",
        30,
        nullptr,
        //设置加载中文
        io.Fonts->GetGlyphRangesChineseFull()
    );
    IM_ASSERT(font != nullptr); // 判断字体加载是否成功
}

// ===================================================
// 初始化渲染资源（着色器、顶点对象、贴图）
// 从原 Application.cpp 的 main() 初始化部分迁移
// ===================================================
void Application::InitResources()
{
    // GLSL文件路径
    // 灯光
    const char* lightVS     = "GLSL/lightVS.glsl";
    const char* lightFS     = "GLSL/lightFS.glsl";
    // 灯光模型
    const char* lightMeshVS = "GLSL/lightMeshVS.glsl";
    const char* lightMeshFS = "GLSL/lightMeshFS.glsl";
    // 模型
    const char* modelVS     = "GLSL/modelVS.glsl";
    const char* modelFS     = "GLSL/modelFS.glsl";
    // 深度
    const char* depthVS     = "GLSL/depthVS.glsl";
    const char* depthFS     = "GLSL/depthFS.glsl";
    // 模板
    const char* stencilVS   = "GLSL/stencilVS.glsl";
    const char* stencilFS   = "GLSL/stencilFS.glsl";
    // alpha
    const char* alphaVS     = "GLSL/alphaVS.glsl";
    const char* alphaFS     = "GLSL/alphaFS.glsl";
    // post
    const char* rtVS        = "GLSL/rtVS.glsl";
    const char* rtFS        = "GLSL/rtFS.glsl";

    // 加载编译着色器
    shader_Model        = new Shader(modelVS, modelFS);             // 定义模型着色器
    shader_Light        = new Shader(lightVS, lightFS);             // 定义灯光着色器
    shader_LightMesh    = new Shader(lightMeshVS, lightMeshFS);     // 定义灯光模型着色器
    shader_Depth        = new Shader(depthVS, depthFS);             // 深度模型着色器
    shader_StencilTest  = new Shader(stencilVS, lightMeshFS);       // 模板测试着色器
    shader_AlphaTest    = new Shader(alphaVS, alphaFS);             // Alpha测试着色器
    shader_RenderTarget = new Shader(rtVS, rtFS);                   // 帧缓冲着色器

    //Model model("model/backpack/backpack.obj");//从文件读取模型

    // 创建顶点对象
    //Vertexs vertexs(vertices, sizeof(vertices), idex, idexSize);//创建、绑定缓冲//载入数据
    cubeV  = new Vertexs(Resource::cubeVertices,  Resource::cubeVerticesSize,  Resource::idexs, 2);
    planV  = new Vertexs(Resource::planeVertices, Resource::planeVerticesSize, Resource::idexs, 2);
    alphaV = new Vertexs(Resource::alphaVertices, Resource::alphaVerticesSize, Resource::idexs, 2);

    // 加载贴图
    cubeTexture  = setTexture("Texture/wall.jpg",                        0, true,  GL_RGB);
    floorTexture = setTexture("Texture/container.jpg",                   0, true,  GL_RGB);
    alpheTexture = setTexture("Texture/blending_transparent_window.png", 0, false, GL_RGBA);

    //------------------------------------- UI -----------------------------------
#pragma region

    //shader_Depth.Use();
    //shader_Depth.setInt("texture1", 0);

#pragma endregion

    // 初始化 DebugUI
    DebugUI::Init();
}

// ===================================================
// 每帧渲染 ImGui
// ===================================================
void Application::RenderImGui()
{
    //---------------------ImGui UI框架------------------
    glfwPollEvents(); // 检查触发事件,更新窗口状态,并调用对应的回调函数

    // Start the Dear ImGui frame启动ImGui框架
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    DebugUI::Draw();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// ===================================================
// 主循环（从原 Application.cpp 的 main() 渲染循环迁移）
// ===================================================
void Application::Run()
{
    //-------------------------------Render loop渲染循环------------------------------
    // 帧时间
    float deltaTime = 0.0f;  // 两帧之间时间差
    float lastFrame = 0.0f;  // 上一帧的时间

    while (!glfwWindowShouldClose(window)) // 在GLFW退出之前一直保持运行//每次循环检查一次glfw是否要退出
    {
        // 帧时间
        float currentFrame = static_cast<float>(glfwGetTime()); // 获取运行秒数
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        scene.deltaTime = deltaTime;

        // 键盘输入
        scene.camera.processInput(window, deltaTime);

        // 渲染场景（Renderer内部处理清屏、各渲染通道）
        renderer.Render(
            scene,
            *shader_StencilTest,
            *shader_Depth,
            *shader_Model,
            *shader_LightMesh,
            *shader_AlphaTest,
            *planV,
            *cubeV,
            *alphaV,
            floorTexture,
            alpheTexture
        );

        // ImGui UI
        RenderImGui();

        // 交换前后缓冲区
        glfwSwapBuffers(window);
    }
}

// ===================================================
// 清理资源（从原 Application.cpp 的 main() 末尾迁移）
// ===================================================
void Application::CleanupResources()
{
    // 删除顶点缓冲
    delete cubeV;   cubeV  = nullptr;
    delete planV;   planV  = nullptr;
    delete alphaV;  alphaV = nullptr;

    // 删除着色器程序
    if (shader_Model)        { shader_Model->DeleteProgram();       delete shader_Model;       shader_Model       = nullptr; }
    if (shader_Depth)        { shader_Depth->DeleteProgram();       delete shader_Depth;       shader_Depth       = nullptr; }
    if (shader_Light)        { shader_Light->DeleteProgram();       delete shader_Light;       shader_Light       = nullptr; }
    if (shader_LightMesh)    { shader_LightMesh->DeleteProgram();   delete shader_LightMesh;   shader_LightMesh   = nullptr; }
    if (shader_StencilTest)  { shader_StencilTest->DeleteProgram(); delete shader_StencilTest; shader_StencilTest = nullptr; }
    if (shader_AlphaTest)    { shader_AlphaTest->DeleteProgram();   delete shader_AlphaTest;   shader_AlphaTest   = nullptr; }
    if (shader_RenderTarget) { shader_RenderTarget->DeleteProgram();delete shader_RenderTarget;shader_RenderTarget = nullptr; }

    // 清理ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate(); // 清理缓存
}
