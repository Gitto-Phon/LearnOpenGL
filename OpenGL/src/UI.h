#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//初始化参数
glm::vec3 backGroundColor = glm::vec3(0.1f, 0.1f, 0.1f);//背景颜色

//模型变换
glm::vec3 modelPos = glm::vec3(0.0f);
glm::vec3 modelScale = glm::vec3(1.0f);

glm::vec3 lightPos(1.2, 1.0, 2.0);      //灯光位置
glm::vec3 lightColor(1.0, 1.0, 1.0);    //灯光颜色
float lightRange = 3.0;                 //灯光范围
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

dirLight dirLight_0;
pointLight pointLight_0;
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