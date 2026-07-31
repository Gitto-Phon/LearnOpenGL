#include "StencilPass.h"

// ===================================================
// 【Step03.2】StencilPass.cpp - 模板测试描边渲染通道实现
// 职责：绘制地板 + 立方体 + 模板描边效果
// 执行子步骤：
//   Step03.2a  绘制地板（禁用模板写入，模板值保持为 0）
//   Step03.2b  绘制立方体（模板缓冲写入 1，颜色写入）
//   Step03.2c  绘制放大立方体描边（模板值 ≠ 1 才绘制，仅边框）
// ===================================================

#include <glad/glad.h>
#include "Resource/Shader.h"
#include "Resource/VertexArray.h"

// ===================================================
// StencilPass - 模板测试渲染：绘制地板 + 两个立方体（带描边效果）
// ===================================================

void StencilPass::Execute(
    const glm::mat4& view,
    const glm::mat4& proj,
    Shader& shader_StencilTest,
    Shader& shader_Depth,
    Vertexs& planV,
    Vertexs& cubeV,
    unsigned int floorTexture
)
{
    shader_StencilTest.Use();
    shader_StencilTest.setMat4("view", view);
    shader_StencilTest.setMat4("proj", proj);
    shader_Depth.Use();
    shader_Depth.setMat4("view", view);
    shader_Depth.setMat4("proj", proj);

    // plane 平面（不做模板测试）
    glStencilMask(0x00);                                           // 禁用模板测试(关闭模板缓冲写入)
    planV.useVAO();
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    shader_Depth.setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // cube 立方体（带模板测试）
    glStencilMask(0xFF);                                           // 启用模板测试
    glStencilFunc(GL_ALWAYS, 1, 0xFF);                             // 设置模板测试，这里是渲染正常模型
    // 永远通过模板测试，通过的测试的片段的模板值都设置为1（前面的StencilOp函数行为）
    cubeV.useVAO();
    //glBindTexture(GL_TEXTURE_2D, cubeTexture);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    shader_Depth.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    shader_Depth.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // 描边边框
    glStencilMask(0x00);                                           // 禁用模板测试
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);                           // 为边框设置模板测试条件，不等于1的像素通过测试
    //if(value != 1), 0xFF
    glDisable(GL_DEPTH_TEST);                                      // 关闭深度测试

    float scale = 1.1f;                                            // 边框大小（原模型缩放值）

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

    // 恢复模板测试默认值
    glStencilMask(0xFF);                                           // 开启模板测试
    glStencilFunc(GL_ALWAYS, 0, 0xFF);                             // 恢复模板测试默认值
    glEnable(GL_DEPTH_TEST);                                       // 开启深度测试
}
