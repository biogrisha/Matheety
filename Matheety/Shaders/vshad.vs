#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aCol;

flat out vec4 col;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	col = aCol;
	gl_Position = projection * view * vec4(aPos.xyz, 1.0f);
	
}