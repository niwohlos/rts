#version 120


varying vec2 vf_texcoord;

uniform sampler2D height_map;


void main(void)
{
    gl_FragColor = vec4(texture2D(height_map, vf_texcoord).rrr, 1.);
}
