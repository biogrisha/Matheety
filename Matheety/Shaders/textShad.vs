#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aTextPar;

out VS_OUT {
    vec2 pos1;
    vec2 pos2;
} vs_out;

uniform mat4 view;
uniform mat4 projection;
void main()
{
	vs_out.pos1 = aTextPar.xy;
	vs_out.pos2 = aTextPar.zw;
	gl_Position = projection * view * vec4(aPos.xyz, 1.0f);
	
}