#version 330 core


in vec2 vf_texcoord;

layout(location = 0) out vec4 color;

uniform mat3 normal_matrix;
uniform sampler2D ter_texture;
uniform sampler2D normal_height;
uniform vec3 incoming_light;


void main(void)
{
    vec3 normal = normalize(normal_matrix * (texture2D(normal_height, vf_texcoord).xzy * 2.0 - vec3(1.0, 1.0, 1.0)));

    vec3 color = texture2D(ter_texture, vf_texcoord).rgb;

    color = vec4(color * max(dot(normal, incoming_light), 0.0), 1.0);
}
