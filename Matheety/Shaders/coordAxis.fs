#version 330 core
out vec4 FragColor;

flat in vec3 col;
void main()
{    
    FragColor = vec4((col.xyz/10)+0.5f,1);
}