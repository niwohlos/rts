#version 330 core


layout(location = 0) in vec2 position;

out vec2 vf_texcoord;

uniform sampler2D height_map;
uniform mat4 mvp;


void main(void)
{
    gl_Position = mvp * vec4(position.x, texture2D(height_map, position).r, position.y, 1.0);

    vf_texcoord = position;
}
