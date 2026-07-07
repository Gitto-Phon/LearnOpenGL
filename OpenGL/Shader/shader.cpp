#include "shader.h"

//构造函数读取并构建着色器
//顶点shader文件路径， 像素shader文件路径
Shader::Shader(const char* vs_filePath, const char* fs_filePath)
{
	//----------------------------------加载shader文件---------------------------------------
#pragma region
	//从文件路径中获取顶点/片段着色器
	std::string vertexCode, fragmentCode;//声明着色器代码变量
	std::ifstream vShaderFile, fShaderFile;//input file stream  //声明输入文件流,从文件读取信息
	std::stringstream vShaderStream, fShaderStream;//创建buffer（数据流）
	//保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);//流默认设置的状态掩码是goodbit
	//当数据流状态变成设置的failbit或者badbit状态时会抛出一个异常
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//所以try中没有thrwo语句,而catch语句还能正常捕获
	try
	{
		//从文件路径中获取顶点/片段着色器
		vShaderFile.open(vs_filePath);//打开文件
		fShaderFile.open(fs_filePath);
		//读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();//把文件写入buffer（read-in data buffer）
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件处理器
		vShaderFile.close();//关闭文件
		fShaderFile.close();
		//转换数据流到string
		vertexCode = vShaderStream.str();//从buffer中读取字符到代码变量中
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();//字符串转换，string转化为c字符串
	const char* fShaderCode = fragmentCode.c_str();
	//等同于
	//const GLchar* vShaderCode = vertexCode.c_str();//string转化为GLchar
#pragma endregion
		//-------------------------------图形渲染管线(Pipeline)---------------------------
	//----------------------------------Compile Shader---------------------------------------
#pragma region
	//VertexShader
	vertex = glCreateShader(GL_VERTEX_SHADER);//创建着色器对象
	glShaderSource(vertex, 1, &vShaderCode, NULL);//设置着色器，着色器源代码附加到着色器对象上
	glCompileShader(vertex);//编译着色器
	//打印编译错误
	checkCompileError(vertex, "VERTEX");//检测编译

	//FragmentShader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);//创建shader
	glShaderSource(fragment, 1, &fShaderCode, NULL);//设置shader
	glCompileShader(fragment);//编译shader
	//Print
	checkCompileError(fragment, "FRAGMENT");

	//ShaderProgram
	ID = glCreateProgram();//创建程序对象
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//Print
	checkCompileError(ID, "LINK");//检测链接

	//Delete Shader//着色器对象链接程序对象之后,删除着色器对象
	glDeleteShader(vertex);
	glDeleteShader(fragment);
#pragma endregion
}
//使用激活程序
void  Shader::Use() const
{   //调用glUseProgram函数激活程序对象
	glUseProgram(ID);
}
//使用删除程序
void Shader::DeleteProgram() const
{
	glDeleteProgram(ID);
}
//uniform工具函数        //设置Uniform之前必须先激活着色器程序//因为是在当前激活的着色器程序中设置的
void Shader::setBool(const std::string& name, const bool& value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	/*
	glGetUniformLocation查询uniform变量的位置值,提供着色器程序对象的ID和uniform的名字
	//c_str()  string对象 转向 C字符串(const char*)
	//为glGetUniformLocation函数提供着色器程序和uniform的名字来获得uniform变量的位置值
	//如果没有找到就会返回-1//查找地址不要求激活着色器程序

	glUniform1i设置值 后缀:f - float  i - int   ui - unsigned int   3f - float3(3个float值)   fv - float向量/数组

	uniform是全局变量,可以在任何着色器中定义,无需通过顶点着色器作为中介,顶点着色器不需要这个uniform
	如果声明了uniform但是没有使用,会被编译器静默移除,导致最后编译出的版本中的不会包含它,可能会导致非常麻烦的错误
	*/
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
void Shader::setVec2(const std::string& name, const glm::vec2 &value) const
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
void Shader::setVec4(const std::string& name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& value) const
{
	//Uniform地址，发送矩阵的数量，是否转置（默认列主序），矩阵数据需要用value_ptr转换
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
	//Uniform地址，发送矩阵的数量，是否转置（默认列主序），矩阵数据需要用value_ptr转换
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

//编译错误检测函数
void Shader::checkCompileError(unsigned int shader, std::string type)
{
	int sucess;
	char infoLog[1024];//存储错误消息的容器
	if (type != "LINK")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- -------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- -------------------- -- " << std::endl;
		}
	}
}