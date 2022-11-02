#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


in VS_OUT {
    vec2 pos1;
    vec2 pos2;
} gs_in[];

uniform mat4 projectionOrth;

out vec2 TexCoords;
void main() {    

vec4 vertPos1 = projectionOrth * vec4(gs_in[0].pos1.xy, 0.0, 0.0);
vec4 vertPos2 = projectionOrth * vec4(gs_in[0].pos2.xy, 0.0, 0.0);

gl_Position = gl_in[0].gl_Position + vertPos1;    // 1:bottom-left
TexCoords = vec2(0,1);
EmitVertex();   
gl_Position = gl_in[0].gl_Position + vertPos1 + vec4(vertPos2.x,0,0,0);    // 2:bottom-right
TexCoords = vec2(1,1);
EmitVertex();
gl_Position = gl_in[0].gl_Position + vertPos1 + vec4(0,vertPos2.y,0,0);   // 3:top-left
TexCoords = vec2(0,0);
EmitVertex();
gl_Position = gl_in[0].gl_Position + vertPos1 + vec4(vertPos2.xy,0,0);    // 4:top-right
TexCoords = vec2(1,0);
EmitVertex();
EndPrimitive();

}  


