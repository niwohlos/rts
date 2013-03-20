#version 330 core


in vec2 vf_texcoord;

layout(location = 0) out vec4 color;

uniform sampler2D ter_texture;


void main(void)
{
    color = vec4(texture2D(ter_texture, vf_texcoord).rgb, 1.0);
}
