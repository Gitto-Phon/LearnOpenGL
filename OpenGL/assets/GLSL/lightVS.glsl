#version 460 core		//GPU版本号与glfw初始化对应
//CPU传入数据（模型数据）
layout (location = 0) in vec3 aPos;		//顶点（位置）数据
layout (location = 1) in vec3 aNormal;	//法线数据
layout (location = 2) in vec2 aTexCoords;

//外部（渲染循环）传入参数  MVP
uniform mat4 model;		//模型矩阵
uniform mat4 view;		//投影矩阵
uniform mat4 proj;		//透视矩阵


uniform vec3 lightPos;	//灯光位置

//VertexShader输出FragmentShader数据
out vec3 Normal;	//观察空间下的法线
out vec3 FragPos;	//M矩阵变换后的世界空间模型数据
//out vec3 LightPos;	//观察空间下的灯光位置
out vec2 TexCoords;


void main()
{
   FragPos = vec3(model * vec4(aPos, 1.0));				//模型位置（顶点数据从模型空间转换到世界空间）
   Normal = aNormal;//mat3(transpose(inverse(model))) * aNormal;	//法线矩阵之后的法线向量（不受模型位移缩放影响）//模型矩阵左上角3X3部分的逆矩阵的转置矩阵
   //LightPos = vec3(view * vec4(lightPos, 1.0));					//灯光位置（灯光位置（本身定义时就是世界坐标）从世界空间变换到观察空间）
   TexCoords = aTexCoords;								//UV

   gl_Position = proj * view * vec4(FragPos, 1.0);		//左乘		//输出最终模型顶点位置
}