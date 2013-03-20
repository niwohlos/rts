#version 120


varying vec2 vf_texcoord;

uniform mat3 normal_matrix;
uniform sampler2D ter_texture;
uniform sampler2D height_map;
uniform vec3 incoming_light;


void main(void)
{
    float h1 = texture2D(height_map, vf_texcoord).r;
    float h2 = texture2D(height_map, vf_texcoord + vec2(1. / 512., 0.)).r;
    float h3 = texture2D(height_map, vf_texcoord + vec2(0., 1. / 512.)).r;

    vec3 normal = normalize(normal_matrix * vec3(h2 - h1, 0.01, h3 - h1));

    vec3 color = texture2D(ter_texture, vf_texcoord).rgb;

    gl_FragColor = vec4(color * max(dot(normal, incoming_light), 0.0), 1.0);
}
