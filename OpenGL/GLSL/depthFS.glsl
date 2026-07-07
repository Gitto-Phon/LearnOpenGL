#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
      float z = depth * 2.0 - 1.0;//转化为NDC坐标系[0-1]
      return (2.0 * near * far) / (far + near - z  * (far - near));
}

void main()
{    
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    FragColor = texture(texture1, TexCoords);
    //FragColor = vec4(vec3(depth), 1.0);
}