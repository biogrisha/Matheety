#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;

void main()
{    
    if(texture(text, TexCoords).r < 0.1)
        discard;
    color =  vec4(1.0, 1.0, 1.0, 1.0);
}