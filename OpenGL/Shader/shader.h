#pragma once
#include <glad/glad.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <glm/glm.hpp>//数学库
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
	unsigned int ID;//着色器程序ID
	//构造函数读取并构建着色器
	//顶点着色器路径,片段着色器路径
	Shader(const char* vs_filePath, const char* fs_filePath);
	//使用激活程序
	void Use() const;
	//使用删除程序
	void DeleteProgram() const;
	//uniform工具函数
	void setBool(const std::string& name, const bool& value) const;
	void setInt(const std::string& name, const int& value) const;
	void setFloat(const std::string& name, const float& value) const;

	void setVec2(const std::string& name, const float& x_value, const float& y_value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;

	void setVec3(const std::string& name, const float& x_value, const float& y_value, const float& z_value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;

	void setVec4(const std::string& name, const float& x_value, const float& y_value, const float& z_value, const float& w_value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;

	void setMat3(const std::string& name, const glm::mat3& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;
private:
	unsigned int vertex, fragment;//着色器
	//编译错误检测函数
	void checkCompileError(unsigned int shader, std::string type);
}; 

//帧缓冲类（一种渲染对象，包括了颜色缓冲，深度缓冲和模板缓冲）
class RenderTarget
{
public:
	unsigned int width = 1920;
	unsigned int height = 1080;

	RenderTarget()
	{
		//创建帧缓冲对象
		glGenFramebuffers(1, &FBO);						//创建帧缓冲对象FrameBufferObject
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);			//绑定为激活的帧缓冲（做完操作之后再解绑帧缓冲）

		//创建RenderTarget纹理(只分配内存，并不填充)
		glGenTextures(1, &TEX);
		glBindFramebuffer(GL_TEXTURE_2D, TEX);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	void useFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}
	void useDiffuseFbo()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void delFBO()
	{
		glDeleteFramebuffers(1, &FBO);
	}
private:
	unsigned int FBO;
	unsigned int TEX;
};