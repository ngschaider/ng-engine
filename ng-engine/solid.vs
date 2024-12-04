#version 330 core

in vec3 vertex;
uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xyz, 1.0);
}