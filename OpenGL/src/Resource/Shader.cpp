#include "Shader.h"

// ===================================================
// Step01: 从文件读取着色器源码
// Step02: 编译顶点/片段着色器 + 链接程序
// Step03: 检测编译/链接错误
// ===================================================
Shader::Shader(const char* vs_filePath, const char* fs_filePath)
{
	// ---- 加载着色器文件 ----
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	std::stringstream vShaderStream, fShaderStream;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vs_filePath);
		fShaderFile.open(fs_filePath);
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// ---- 编译着色器 ----
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileError(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileError(fragment, "FRAGMENT");

	// ---- 链接程序 ----
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileError(ID, "LINK");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use() const
{
	glUseProgram(ID);
}

void Shader::DeleteProgram() const
{
	glDeleteProgram(ID);
}

void Shader::setBool(const std::string& name, const bool& value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, const int& value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float& value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const float& x_value, const float& y_value) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x_value, y_value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, const float& x_value, const float& y_value, const float& z_value) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x_value, y_value, z_value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, const float& x_value, const float& y_value, const float& z_value, const float& w_value) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x_value, y_value, z_value, w_value);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::checkCompileError(unsigned int shader, std::string type)
{
	int sucess;
	char infoLog[1024];

	if (type != "LINK")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
			          << infoLog << "\n -- -------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
			          << infoLog << "\n -- -------------------- -- " << std::endl;
		}
	}
}