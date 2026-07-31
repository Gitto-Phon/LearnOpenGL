#include "DebugUI.h"

// ===================================================
// 【Step04】DebugUI.cpp - ImGui 调试面板实现
// 职责：每帧绘制 ImGui 调试窗口，用于运行时调整参数
// 执行顺序（每帧调用一次）：
//   Step04.0  Init()              ← 初始化全局状态（仅首次调用）
//   Step04.1  Draw()              ← 每帧绘制所有调试面板
//   Step04.1a  ShowMainWindow()   ← "Learn OpenGL" 主面板（背景色 + 灯光色）
//   Step04.1b  ShowModelWindow()  ← "模型" 面板（位置/缩放/旋转 参数）
//   Step04.1c  ShowLightWindow()  ← "灯光" 面板（光源参数）
// ===================================================
// 全局变量定义（原 UI.h 中的定义移到这里）
// ===================================================
glm::vec3 backGroundColor = glm::vec3(0.1f, 0.1f, 0.1f);//背景颜色

//模型变换
glm::vec3 modelPos = glm::vec3(0.0f);
glm::vec3 modelScale = glm::vec3(1.0f);

glm::vec3 lightPos(1.2, 1.0, 2.0);      //灯光位置
glm::vec3 lightColor(1.0, 1.0, 1.0);    //灯光颜色
float lightRange = 3.0;                 //灯光范围

dirLight dirLight_0;
pointLight pointLight_0;

// ===================================================
// App 命名空间实现
// ===================================================
namespace App
{
    //选中结果
    bool isShowDrag = false;
    //字符串结果
    std::string text = "";
    //拖拽值
    float fValue = 0.5f;

    bool show_demo_window = false;
    bool show_model_window = false;
    bool show_light_window = false;
    
    static float f = 0.0f;
    static int counter = 0;

    void RenderUI()
    {
        if (show_demo_window) { ImGui::ShowDemoWindow(&show_demo_window); }

        {
            //创建一个设置窗口
            ImGui::Begin("Learn OpenGL");
            //显示文本
            ImGui::Text("显示字符串用");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("模型选项", &show_model_window);
            ImGui::Checkbox("灯光选项", &show_light_window);

            ImGui::ColorEdit3("BackGroundColor", (float*)&backGroundColor);
            ImGui::SliderFloat("lightShader position", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("lightShader color", (float*)&lightColor); // Edit 3 floats representing a color
        //按钮在单击时返回true
            //if (ImGui::Button("Button"))
            //{
            //    counter++;
            //}

            ImGui::SameLine();//显示在同一行
            ImGui::Text("counter = %d", counter);

            ImGui::End();
        }

        //Model
        if (show_model_window)
        {
            ImGui::Begin("模型", &show_model_window);
            //Position
            ImGui::SliderFloat3("ModelPosition", (float*)&modelPos, -10.0f, 10.0f);
            if (ImGui::Button("Pos_Reset"))
            {
                modelPos = glm::vec3(0.0f);
            }
            ImGui::SliderFloat3("ModelScale", (float*) &modelScale, 1.0f, 10.0f);
            if (ImGui::Button("Scale_Reset"))
            {
                modelScale = glm::vec3(1.0f);
            }
            ImGui::SameLine();
            //ImGui::SliderAngle("",);
            //ImGui::InputFloat3("Position", (float*) & modelPos);
            ImGui::End();
        }

        //Light
        if (show_light_window)
        {
            ImGui::Begin("灯光", &show_light_window);
            ImGui::Text("DirLight");
            ImGui::SliderFloat3("DL_dir", (float*)&dirLight_0.direction, -1.0f, 1.0f);
            ImGui::ColorEdit3("DL_ambient", (float*)&dirLight_0.ambient);
            ImGui::ColorEdit3("DL_diffuse", (float*)&dirLight_0.diffuse);
            ImGui::ColorEdit3("DL_specular",(float*)&dirLight_0.specular);
            ImGui::Text("PointLight");
            ImGui::SliderFloat3("PL_Position", (float*)&pointLight_0.position, -10.0f, 10.0f);
            ImGui::ColorEdit3("PL_ambient", (float*)&pointLight_0.ambient);
            ImGui::ColorEdit3("PL_diffuse", (float*)&pointLight_0.diffuse);
            ImGui::ColorEdit3("PL_specular", (float*)&pointLight_0.specular);

            ImGui::End();
        }

    }
}

// ===================================================
// DebugUI::Draw - 每帧绘制 ImGui 调试面板
// 调用 App::RenderUI() → 渲染三个子面板
// ===================================================

namespace DebugUI
{

void Init()
{
    // UI 状态已在全局变量中初始化
    // 此处无需额外初始化
}

void Draw()
{
    // 调用 App::RenderUI()（保持原 ImGui 代码不变）
    App::RenderUI();
}

} // namespace DebugUI