#version 460 core
out vec4 FragColor;

//顶点着色器传入参数
in vec3 Normal;
in vec3 VertexPos;
in vec2 TexCoords;

//外部（渲染循环）传入参数
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;

#pragma region
struct Light
{
	//vec3 lightPos;	//灯光位置
	vec3 dir;			//灯光方向

	vec3 pos;			//聚光灯位置
	float cutoff;		//聚光灯角度余弦值
	float cutoff2;		//聚光灯外围角度余弦值

	vec3 ambient;		//环境光颜色
	vec3 diffuse;		//漫反射颜色
	vec3 specular;		//高光颜色

	float constant;		//常数项	通常为1（为了保证分母大于1）
	float linear;		//一次项	50-100距离  0.09-0.045
	float quadratic;	//二次项	50-100距离	0.032-0.0075
};
uniform Light light;	//灯光颜色

struct Material
{
	//vec3 ambient;		//环境光颜色  =  漫反射颜色
	sampler2D diffuse;	//漫反射颜色
	sampler2D specular;	//高光颜色
	float shininess;	//高光散射（范围）系数
};
uniform Material material; //声明Material类型的uniform变量

struct DirLight          //方向光结构体
{
	vec3 dir;		//定向光方向

	vec3 ambient;		//定向光环境光颜色
	vec3 diffuse;		//定向光漫反射颜色
	vec3 specular;		//定向光高光颜色
};
uniform DirLight dirLight;
vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir);

struct PointLight		//点光源结构体
{
	vec3 pos;		//点光源位置

	float constant;
	float linear;
	float quadratic;

	vec3 cutoff;		//点光源半径

	vec3 ambient;		//点光源环境光颜色
	vec3 diffuse;		//点光源漫反射颜色
	vec3 specular;		//点光源高光颜色
};
//#define NR_POINT_LIGHTS 4
//uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform PointLight pointLight;
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir);

struct SpotLight		//聚光灯结构体
{
	vec3 pos;		//聚光灯位置
	vec3 dir;		//聚光灯方向
	float cutoff_inner;	//聚光灯内圈角度cos值
	float cutoff_outer;	//聚光灯外圈角度cos值

	float constant;		//常数项
	float linear;		//一次线性项
	float quadratic;	//二次项

	vec3 ambient;		//聚光灯环境光颜色
	vec3 diffuse;		//聚光灯漫反射颜色
	vec3 specular;		//聚光灯高光颜色
};
uniform SpotLight spotLight;
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 viewDir);
#pragma endregion

void main()
{
   vec3 diffuse = vec3(texture(material.diffuse, TexCoords));
   vec3 specular =	vec3(texture(material.specular, TexCoords));

#pragma region
	
//   //环境光
//   vec3 ambient = diffuse * light.ambient; //环境光 * 灯光颜色
//   //漫反射
   vec3 norm = normalize(Normal);				//法线向量
//   vec3 lDir = normalize(light.pos - VertexPos);	//灯光方向向量
//   float lambert = max(dot(norm, lDir), 0.0);	//兰伯特光照
//   diffuse = diffuse * lambert * light.diffuse;	//基础颜色 * 环境光 * 灯光颜色
//   //Specular镜面光
   vec3 viewDir = normalize(viewPos - VertexPos);	//摄像机向量
//   vec3 rDir = reflect(-lDir, norm);	//反射向量
//   float spec = pow(max(dot(rDir, viewDir ), 0.0), material.shininess);  //高光范围
//   specular = specular * spec * light.specular; //高光强度 * 范围 * 灯光颜色
   
#pragma endregion

   //------------------------------光照合并-----------------------------
   vec3 result;//定义最终的输出颜色变量
   //第一阶段：定向光
   result += CalculateDirLight(dirLight, norm, viewDir);
   //第二阶段：点光源
   //for(int i = 0; i < NR_POINT_LIGHTS; i++){
	//	result += CalculatePointLight(pointLight[i], norm, viewDir);
	//}
	result += CalculatePointLight(pointLight, norm, viewDir);
	FragColor = vec4(result, 1.0);
	//第三阶段：聚光灯
	//result += CalculateSpotLight(spotLight, norm, viewDir);

   //vec3 result = (ambient + diffuse + specular) * attenuation;	//最终输出颜色（布林冯光照模型） = 环境光 + 基础颜色 + 高光
   //FragColor = texture(material.specular, TexCoords);
}

//------------------------------------------灯光函数--------------------------------------------
//方向光函数实现   太阳光，法线，相机方向
vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.dir);
	//漫反射着色
	float diff = max(dot(lightDir, normal), 0.0);//兰伯特
	//高光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	//合并光照
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords)) * diff;
	vec3 specular = light.specular * vec3(texture(material.specular, TexCoords)) * spec;
	vec3 result = (ambient + diffuse + specular);
	return result;
}
//点光源函数实现
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - VertexPos);//像素指向灯光的向量
	//漫反射着色
	float diff = max(dot(lightDir, normal), 0.0);
	//高光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	//衰减
	float distance = length(light.pos - VertexPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	//合并光照
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords)) * diff;
	vec3 specular = light.specular * vec3(texture(material.specular, TexCoords)) * spec;
	vec3 result = (ambient + diffuse + specular) * attenuation;
	return result;
}
//聚光灯函数实现
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.dir);
	//漫反射着色
	float diff = max(dot(lightDir, normal), 0.0);
	//高光着色
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
	//边缘过渡
	float theta = dot(lightDir, normalize(light.pos - VertexPos));
	float eplison = light.cutoff_inner - light.cutoff_outer;
	float intensity = clamp((theta - light.cutoff_outer) / eplison, 0.0f, 1.0f);
	//距离衰减
	float distance = length(light.pos - VertexPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//合并光照
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords)) * diff;
	vec3 specular = light.specular * vec3(texture(material.specular, TexCoords)) * spec;
	vec3 result = ambient + (diffuse + specular) * intensity * attenuation;
	return result;
}



//   //环境光
//   vec3 ambient = diffuse * light.ambient; //环境光强度 * 灯光颜色
//   //漫反射
//   vec3 norm = normalize(Normal);				//法线向量
//   vec3 lDir = normalize(light.pos - VertexPos);	//灯光方向向量
//   float lambert = max(dot(norm, lDir), 0.0);	//兰伯特光照
//   diffuse = diffuse * lambert * light.diffuse;	//基础颜色（漫反射颜色） * 漫反射强度范围 * 灯光颜色
//   //Specular镜面光
//   vec3 viewDir = normalize(viewPos - VertexPos);	//摄像机向量
//   vec3 rDir = reflect(-lDir, norm);	//反射向量
//   float spec = pow(max(dot(rDir, viewDir ), 0.0), material.shininess);  //高光范围
//   specular = specular * spec * light.specular; //高光强度 * 范围 * 灯光颜色