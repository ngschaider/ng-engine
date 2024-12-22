#version 330 core

in vec4 vertex; // <vec2 position, vec2 texCoords>
out vec2 TexCoords;
uniform mat4 transformationMatrix;

void main() {
    TexCoords = vertex.zw;
    gl_Position = transformationMatrix * vec4(vertex.xy, 0.0, 1.0);
}