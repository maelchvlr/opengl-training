#version 450 core

in vec4 position;
uniform float time;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;


void main(void)
{
    gl_Position = proj_matrix * mv_matrix * position;
    float timeFactor = sin(time) * 0.5 + 0.5;

    vs_out.color = position * timeFactor + vec4(0.5, 0.5, 0.5, 0.0);
}
