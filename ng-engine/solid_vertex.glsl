#version 330 core

in vec3 vertex;
uniform mat4 transformationMatrix;

void main()
{
    gl_Position = transformationMatrix * vec4(vertex.xyz, 1.0);
}