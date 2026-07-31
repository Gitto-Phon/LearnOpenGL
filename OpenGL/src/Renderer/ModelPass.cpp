#include "ModelPass.h"

// ===================================================
// 【Step03.1】ModelPass.cpp - 模型+光照渲染通道实现
// 职责：渲染 3D 模型（立方体 + 灯光方块）
// 执行子步骤：
//   Step03.1a  绘制立方体（模型着色器 + 光照计算）
//   Step03.1b  绘制灯光方块（灯光模型着色器）
// ===================================================

#include <glad/glad.h>
#include "Resource/Shader.h"
#include "Resource/VertexArray.h"
#include "Resource/Model.h"

// ===================================================
// ModelPass - 模型 + 光照渲染（当前多数代码为注释状态）
// ===================================================

void ModelPass::Execute(
    const glm::mat4& view,
    const glm::mat4& proj,
    Shader& shader_Model,
    Shader& shader_LightMesh,
    Vertexs& cubeV,
    Model* model
)
{
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

        (void)view;          // 抑制未使用参数警告
        (void)proj;
        (void)shader_Model;
        (void)shader_LightMesh;
        (void)cubeV;
        (void)model;
    }
}
