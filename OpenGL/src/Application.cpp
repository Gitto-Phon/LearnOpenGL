#pragma once
#include "Application.h"

//GLSL文件路径
//灯光
const char* lightVS = "GLSL/lightVS.glsl";
const char* lightFS = "GLSL/lightFS.glsl";
//灯光模型
const char* lightMeshVS = "GLSL/lightMeshVS.glsl";
const char* lightMeshFS = "GLSL/lightMeshFS.glsl";
//模型
const char* modelVS = "GLSL/modelVS.glsl";
const char* modelFS = "GLSL/modelFS.glsl";
//深度
const char* depthVS = "GLSL/depthVS.glsl";
const char* depthFS = "GLSL/depthFS.glsl";
//模板
const char* stencilVS = "GLSL/stencilVS.glsl";
const char* stencilFS = "GLSL/stencilFS.glsl";
//alpha
const char* alphaVS = "GLSL/alphaVS.glsl";
const char* alphaFS = "GLSL/alphaFS.glsl";
//post
const char* rtVS = "GLSL/rtVS.glsl";
const char* rtFS = "GLSL/rtFS.glsl";

int main(void)
{
    GLFWwindow* window = glInit(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");//窗口初始化

    //加载编译着色器
    Shader shader_Model(modelVS, modelFS);                      //定义模型着色器
    Shader shader_Light(lightVS, lightFS);                              //定义灯光着色器
    Shader shader_LightMesh(lightMeshVS, lightMeshFS);   //定义灯光模型着色器
    Shader shader_Depth(depthVS, depthFS);                          //深度模型着色器
    Shader shader_StencilTest(stencilVS, lightMeshFS);          //模板测试着色器
    Shader shader_AlphaTest(alphaVS, alphaFS);                  //Alpha测试着色器
    Shader shader_RenderTarget(rtVS, rtFS);                     //帧缓冲着色器

    //Model model("model/backpack/backpack.obj");//从文件读取模型

    //Vertexs vertexs(vertices, sizeof(vertices), idex, idexSize);//创建、绑定缓冲//载入数据
    Vertexs cubeV(cubeVertices, sizeof(cubeVertices), idexs, 2);
    Vertexs planV(planeVertices, sizeof(planeVertices), idexs, 2);
    Vertexs alphaV(alphaVertices, sizeof(alphaVertices), idexs, 2);
    unsigned int cubeTexture = setTexture("Texture/wall.jpg", 0, true, GL_RGB);
    unsigned int floorTexture = setTexture("Texture/container.jpg", 0, true, GL_RGB);
    unsigned int alpheTexture = setTexture("Texture/blending_transparent_window.png", 0, false, GL_RGBA);
    //------------------------------------- UI -----------------------------------
#pragma region

    //shader_Depth.Use();
    //shader_Depth.setInt("texture1", 0);

#pragma endregion
    //-------------------------------Render loop渲染循环------------------------------
    //帧时间
    float deltaTime = 0;//两帧之间时间差
    float lastFrame = 0;//上一帧的时间

    while (!glfwWindowShouldClose(window))//在GLFW退出之前一直保持运行//每次循环检查一次glfw是否要退出
    {
#pragma region
        //帧时间
        float currentFrame = static_cast<float>(glfwGetTime());//获取运行秒数
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processInput(window, deltaTime);//键盘输入
        //初始化
        glClearColor(backGroundColor.x, backGroundColor.y, backGroundColor.z, 1.0f);//设置清空屏幕所用的颜色//状态设置函数
        //清空屏幕（缓冲位：BUFFER_BIT 可用的有GL_COLOR_...  GL_DEPTH_...  GL_STENCIL_...）
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//清除前一帧的颜色缓冲和深度缓冲//状态使用函数
        //开启了深度测试和模板测试，需要在每帧前清除缓冲，也就是更新缓冲
        
        //初始化MVP矩阵
        glm::mat4 model = glm::mat4(1.0f);                  //初始化模型矩阵
        glm::mat4 view = camera.getViewMat();               //初始化观察矩阵
        glm::mat4 proj = camera.getProjectionMat();         //初始化透视矩阵
#pragma endregion
        //渲染指令
        
        //STL库的map数据结构，会自动根据键值对它的值排序(这里的键值是每个窗户对应的距离)
        std::map<float, glm::vec3> sorted;
        for (unsigned int i = 0; i < windows.size(); i++)
        {
            float distance = glm::length(camera.cameraPos - windows[i]);
            sorted[distance] = windows[i];//每个窗户给存一个距离键值，按低到高排序
        }

        //------------model---------------
        //shader_Model.Use();              //激活程序对象

        //传入MVP矩阵到VertexShader
        {
        //------------Light----------
        
            //shader_Model.setVec3("viewPos", camera.cameraPos);
            //shader_Model.setFloat("material.shininess", 32.0f);

            //// directional light
            //shader_Model.setVec3("dirLight.dir", dirLight_0.direction);
            //shader_Model.setVec3("dirLight.ambient", dirLight_0.ambient);
            //shader_Model.setVec3("dirLight.diffuse", dirLight_0.diffuse);
            //shader_Model.setVec3("dirLight.specular", dirLight_0.specular);
            //// point light 1
            //pointLight_0.position = glm::vec3(cos(currentFrame), 1.0f, sin(currentFrame));
            //shader_Model.setVec3("pointLight.pos", pointLight_0.position);
            //shader_Model.setVec3("pointLight.ambient", pointLight_0.ambient);
            //shader_Model.setVec3("pointLight.diffuse", pointLight_0.diffuse);
            //shader_Model.setVec3("pointLight.specular", pointLight_0.specular);
            //shader_Model.setFloat("pointLight.constant", 1.0f);
            //shader_Model.setFloat("pointLight.linear", 0.09f);
            //shader_Model.setFloat("pointLight.quadratic", 0.032f);

            // spotLight
            //shader_Model.setVec3("spotLight.position", camera.cameraPos);
            //shader_Model.setVec3("spotLight.direction", camera.cameraFront);
            //shader_Model.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            //shader_Model.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            //shader_Model.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
            //shader_Model.setFloat("spotLight.constant", 1.0f);
            //shader_Model.setFloat("spotLight.linear", 0.09f);
            //shader_Model.setFloat("spotLight.quadratic", 0.032f);
            //shader_Model.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
            //shader_Model.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

            //// view/projection transformations
            //shader_Model.setMat4("view", view);
            //shader_Model.setMat4("proj", proj);

            //// world transformation
            //model = glm::translate(model, modelPos);
            //model = glm::scale(model, modelScale);
            //shader_Model.setMat4("model", model);

            //model.Draw(shader_Model);

            ////定义灯光着色器
            //shader_LightMesh.Use();
            //glm::mat4 model = glm::mat4(1.0f);
            //shader_LightMesh.setMat4("view", view);
            //shader_LightMesh.setMat4("proj", proj);
        
            //shader_LightMesh.setVec3("lightColor", lightColor);        //灯光颜色
            //model = glm::translate(model, pointLight_0.position);          //设置灯光位置
            //model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));      //设置灯光模型大小
            //shader_LightMesh.setMat4("model", model);
            //glDrawArrays(GL_TRIANGLES, 0, 36);

            //-------------绘制----------
            //if (drawLight) {
            //    for (int i = 0; i < 4; i++) {
            //        glm::mat4 model = glm::mat4(1.0f);
            //        model = glm::translate(model, pointlightPositions[i]);          //设置灯光位置
            //        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));      //设置灯光模型大小
            //        shader_LightMesh.setMat4("model", model);
            //        glDrawArrays(GL_TRIANGLES, 0, 36);
            //    }
            //}

            shader_StencilTest.Use();
            shader_StencilTest.setMat4("view", view);
            shader_StencilTest.setMat4("proj", proj);
            shader_Depth.Use();
            shader_Depth.setMat4("view", view);
            shader_Depth.setMat4("proj", proj);
            
            //plane
            glStencilMask(0x00);//禁用模板测试(关闭模板缓冲写入)
            planV.useVAO();
            glBindTexture(GL_TEXTURE_2D, floorTexture);
            shader_Depth.setMat4("model", glm::mat4(1.0f));
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //cube
            glStencilMask(0xFF);//启用模板测试
            glStencilFunc(GL_ALWAYS, 1, 0xFF);//设置模板测试，这里是渲染正常模型
            //永远通过模板测试，通过的测试的片段的模板值都设置为1（前面的StencilOp函数行为）
            cubeV.useVAO();
            //glBindTexture(GL_TEXTURE_2D, cubeTexture);
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            shader_Depth.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            shader_Depth.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glStencilMask(0x00);//禁用模板测试
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);//为边框设置模板测试条件，不等于1的像素通过测试
            //if(value != 1), 0xFF
            glDisable(GL_DEPTH_TEST);//关闭深度测试

            float scale = 1.1f;//边框大小（原模型缩放值）

            shader_StencilTest.Use();
            cubeV.useVAO();
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            shader_StencilTest.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            shader_StencilTest.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glStencilMask(0xFF);//开启模板测试
            glStencilFunc(GL_ALWAYS, 0, 0xFF);//恢复模板测试默认值
            glEnable(GL_DEPTH_TEST);//开启深度测试

            //shader_AlphaTest.Use();
            //shader_AlphaTest.setMat4("view", view);
            //shader_AlphaTest.setMat4("proj", proj);

            //planV.useVAO();
            //glBindTexture(GL_TEXTURE_2D, floorTexture);
            //shader_AlphaTest.setMat4("model", glm::mat4(1.0f));
            //glDrawArrays(GL_TRIANGLES, 0, 6);

            //cubeV.useVAO();
            //glBindTexture(GL_TEXTURE_2D, floorTexture);
            //model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            //shader_AlphaTest.setMat4("model", model);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
            //model = glm::mat4(1.0f);
            //model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            //shader_AlphaTest.setMat4("model", model);
            //glDrawArrays(GL_TRIANGLES, 0, 36);

            //alphaV.useVAO();
            //glBindTexture(GL_TEXTURE_2D, alpheTexture);

            ////反向迭代器（reverse iterator）,反向遍历
            //for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
            //{
            //    model = glm::mat4(1.0f);
            //    model = glm::translate(model, it->second);
            //    shader_AlphaTest.setMat4("model", model);
            //    glDrawArrays(GL_TRIANGLES, 0, 6);
            //}
        }

        //---------------------ImGui UI框架------------------
        glfwPollEvents();//检查触发事件,更新窗口状态,并调用对应的回调函数

        // Start the Dear ImGui frame启动ImGui框架
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        App::RenderUI();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);//交换前后帧
    }
    //vertexs.deleteBuffer();//清理缓冲
    shader_Model.DeleteProgram();//删除程序对象
    shader_Depth.DeleteProgram();

    //清理ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();//清理缓存
    return 0;
}