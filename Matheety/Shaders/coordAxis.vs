#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

flat out vec3 col;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	col = aPos.xyz;
	gl_Position = projection * view * vec4(aPos, 1.0f);
	
}