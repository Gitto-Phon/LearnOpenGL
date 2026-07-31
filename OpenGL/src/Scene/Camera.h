#pragma once

// Camera.h - 摄像机
// 从原 src/camera.h 移入
// 职责：FPS 摄像机控制（WASD + 鼠标 + 滚轮），提供 view/projection 矩阵

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//窗口尺寸
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

//相机移动方向
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

//设置相机默认值
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
//近平面、远平面
const float nearPlan = 0.1f;
const float farPlan = 100.0f;

class Camera
{
public:
    //相机属性
    glm::vec3 cameraPos;//摄像机位置
    glm::vec3 cameraFront;//摄像机向前向量
    glm::vec3 cameraRight;//摄像机向右向量
    glm::vec3 cameraUp;//摄像机向上向量
    glm::vec3 worldUp;//世界空间向上向量
    //欧拉角
    float Yaw;
    float Pitch;
    //相机选项
    float zoom;         //相机推拉
    float movementSpeed;//移动速度
    float mouseSensitivity;//鼠标灵敏度

    //Camera(zoom, movementSpeed, mouseSensitivity, cameraPos)
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        cameraPos = position;
        worldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVector();
    }
    //窗口监听
    void frambuffer_size_callback(int width, int height)
    {
        glViewport(0, 0, width, height);//前两个控制左下角,后两个右上角(像素)
    }
    //鼠标监听
    void mouse_callback(double xposIn, double yposIn)
    {
        float xPos = static_cast<float>(xposIn);
        float yPos = static_cast<float>(yposIn);
        if (firstMouse)//初始化
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }
        float xoffset = xPos - lastX;
        float yoffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;//鼠标偏移量
        Yaw += xoffset;
        Pitch += yoffset;
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;//俯仰角限制

        updateCameraVector();
    }
    //鼠标滚轮——改变zoom
    void scroll_callback(double yposIn)
    {
        float yPos = static_cast<float>(yposIn);
        zoom -= yPos;
        if (zoom < 1) zoom = 1;
        if (zoom > 90) zoom = 90;
    }
    //键盘输入
    void processInput(GLFWwindow* window, float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//判断是否按下esc键
        {
            glfwSetWindowShouldClose(window, true);//关闭glfw
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            ProcessKeyboard(FORWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            ProcessKeyboard(BACKWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            ProcessKeyboard(LEFT, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            ProcessKeyboard(RIGHT, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            ProcessKeyboard(UP, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            ProcessKeyboard(DOWN, deltaTime);
        }
        //if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
        //{
        //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        //}
        //if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        //{
        //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //}
    }

    //观察矩阵  世界到观察
    glm::mat4 getViewMat()
    {
        //return glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
        return getLookAt(cameraPos, cameraPos + cameraFront, worldUp);
        //return getLookAt();
    }

    //LookAt
    glm::mat4 getLookAt(glm::vec3 cPos, glm::vec3 oPos, glm::vec3 wUp)
    {
        //glm::mat4 mat = glm::mat4(  rDir.x, uDir.x, fDir.x, 0, 
        //                            rDir.y, uDir.y, fDir.y, 0, 
        //                            rDir.z, uDir.z, fDir.z, 0,
        //                            -glm::dot(cPos, rDir), -glm::dot(cPos, uDir), -glm::dot(cPos, fDir), 1);
        glm::mat4 mat = glm::mat4(1);
        glm::vec3 z = glm::normalize(oPos - cPos);
        z = -z;
        glm::vec3 x = glm::normalize(glm::cross(wUp, z));
        glm::vec3 y = glm::normalize(glm::cross(z, x));

        glm::vec4 fDir = glm::vec4(z, -glm::dot(cPos, z));
        glm::vec4 rDir = glm::vec4(x, -glm::dot(cPos, x));
        glm::vec4 uDir = glm::vec4(y, -glm::dot(cPos, y));
        mat = glm::mat4(rDir, uDir, fDir, glm::vec4(0,0,0,1));
        return glm::transpose(mat);
    }
    //---------------------------------投影矩阵--观察到裁剪--正射投影、透视投影
    //透视投影
    glm::mat4 getProjectionMat() const
    {
        return glm::perspective(glm::radians(zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, nearPlan, farPlan);
    }
    //正射投影
    glm::mat4 getOrthoMat()
    {
        return glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    }

private:

    //鼠标
    //float lastX;
    //float lastY;
    int count = 0;
    float lastX = (float)SCR_WIDTH / 2.0f;
    float lastY = (float)SCR_HEIGHT / 2.0f;
    bool firstMouse = true;

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        //FPS
        float cameraSpeed = movementSpeed * deltaTime;
        if (direction == FORWARD) { cameraPos += cameraSpeed * cameraFront; }
        if (direction == BACKWARD) { cameraPos -= cameraSpeed * cameraFront; }
        if (direction == LEFT) { cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, worldUp)); }
        if (direction == RIGHT) { cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, worldUp)); }
        if (direction == UP) { cameraPos += cameraSpeed * worldUp; }
        if (direction == DOWN) { cameraPos -= cameraSpeed * worldUp; }
    }

    void updateCameraVector()
    {
        glm::vec3 front(1);//计算最终方向向量
        front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
        front.y = sin(glm::radians(Pitch));
        front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
        cameraFront = glm::normalize(front);
        cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
    }
};