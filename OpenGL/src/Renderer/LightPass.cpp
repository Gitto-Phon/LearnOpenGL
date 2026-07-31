#include "LightPass.h"

#include <glad/glad.h>
#include "Shader/shader.h"
#include "Resource/VertexArray.h"
#include "Resource/GeometryFactory.h"

// ===================================================
// LightPass - 点光源渲染（当前代码为注释状态）
// ===================================================

void LightPass::Execute(
    const glm::mat4& view,
    const glm::mat4& proj,
    Shader& shader_LightMesh,
    Vertexs& cubeV
)
{
    //-------------绘制（灯光方块）----------
    //if (drawLight) {
    //    for (int i = 0; i < 4; i++) {
    //        glm::mat4 model = glm::mat4(1.0f);
    //        model = glm::translate(model, pointlightPositions[i]);          //设置灯光位置
    //        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));      //设置灯光模型大小
    //        shader_LightMesh.setMat4("model", model);
    //        glDrawArrays(GL_TRIANGLES, 0, 36);
    //    }
    //}

    (void)view;              // 抑制未使用参数警告
    (void)proj;
    (void)shader_LightMesh;
    (void)cubeV;
}
