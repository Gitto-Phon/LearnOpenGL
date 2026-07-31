#pragma once
#include <glad/glad.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ===================================================
// Shader - 着色器类
// Step01: 从文件加载顶点/片段着色器源码
// Step02: 编译着色器、链接程序
// Step03: 提供 Use/Delete 接口
// Step04: 提供 Uniform 设置工具函数
// ===================================================
class Shader
{
public:
	unsigned int ID;

	Shader(const char* vs_filePath, const char* fs_filePath);
	void Use() const;
	void DeleteProgram() const;

	void setBool (const std::string& name, const bool&  value) const;
	void setInt  (const std::string& name, const int&   value) const;
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
	unsigned int vertex, fragment;
	void checkCompileError(unsigned int shader, std::string type);
};