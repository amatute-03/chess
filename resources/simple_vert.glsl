#version  330 core
layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec3 vertNor;
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform float bendAmount;
out vec3 fragNor;
uniform vec3 lightP;

void main()
{

    float cur1 = vertPos.z + sin(vertPos.y * bendAmount);
    float cur2 = vertPos.y + sin(vertPos.z * bendAmount);
    float cur3 = vertPos.x + sin(vertPos.z * bendAmount);

	vec3 bentPos = vec3(cur3, cur2, cur1);

	fragNor = (V*M * vec4(vertNor, 0.0)).xyz;

	gl_Position = P * V * M * vec4(bentPos, 1.0);
}
