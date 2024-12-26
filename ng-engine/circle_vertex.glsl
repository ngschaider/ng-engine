#version 330 core

in vec2 value;
in vec3 vertex;

uniform mat4 transformationMatrix;

out vec2 val;

void main()
{
    val = value;
    gl_Position = transformationMatrix * vec4(vertex.xyz, 1.0);
}