#version 120


attribute vec2 position;

varying vec2 vf_texcoord;

uniform sampler2D height_map;
uniform mat4 mvp_matrix;


void main(void)
{
    vec2 vtx_pos = position * 2.0 - vec2(1.0, 1.0);

    gl_Position = mvp_matrix * vec4(vtx_pos.x, texture2D(height_map, position).r / 4., vtx_pos.y, 1.0);

    vf_texcoord = position;
}
