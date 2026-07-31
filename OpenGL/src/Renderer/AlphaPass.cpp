#include "AlphaPass.h"

#include <glad/glad.h>
#include "Shader/shader.h"
#include "Resource/VertexArray.h"
#include "Scene/Camera.h"

// ===================================================
// AlphaPass - Alpha 混合渲染（透明度排序、植被/窗户半透明）
// 当前代码为注释状态
// ===================================================

void AlphaPass::Execute(
    const glm::mat4& view,
    const glm::mat4& proj,
    Shader& shader_AlphaTest,
    Vertexs& planV,
    Vertexs& cubeV,
    Vertexs& alphaV,
    unsigned int floorTexture,
    unsigned int alpheTexture,
    const Camera& camera,
    const std::vector<glm::vec3>& windows
)
{
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

    (void)view;              // 抑制未使用参数警告
    (void)proj;
    (void)shader_AlphaTest;
    (void)planV;
    (void)cubeV;
    (void)alphaV;
    (void)floorTexture;
    (void)alpheTexture;
    (void)camera;
    (void)windows;
}
