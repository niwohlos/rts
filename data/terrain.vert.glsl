#version 330 core


layout(location = 0) in vec2 position;

out vec2 vf_texcoord;

uniform sampler2D height_map;
uniform mat4 mvp;


void main(void)
{
    vec2 vtx_pos = position * 2.0 - vec2(1.0, 1.0);

    gl_Position = mvp * vec4(vtx_pos.x, texture2D(height_map, position).r / 4., vtx_pos.y, 1.0);

    vf_texcoord = position;
}
