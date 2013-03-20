#version 120


varying vec2 vf_texcoord;

uniform sampler2D ter_texture;


void main(void)
{
    gl_FragColor = vec4(texture2D(ter_texture, vf_texcoord).rgb, 1.0);
}
