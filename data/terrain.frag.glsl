#version 330 core


in vec2 texcoord;

layout(location = 0) out vec4 color;

uniform sampler2D height_map;


void main(void)
{
    color = vec4(texture2D(height_map, texcoord).rrr, 1.);
}
