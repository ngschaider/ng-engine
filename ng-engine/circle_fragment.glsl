#version 330 core

uniform vec4 color;

in vec2 val;
out vec4 FragColor;

void main() {
    float R = 1.0;
    float R2 = 0;

    float dist = sqrt(dot(val,val));
    if (dist >= R || dist <= R2) {
        discard;
    }
    //float sm = smoothstep(R,R-0.01,dist);
    //float sm2 = smoothstep(R2,R2+0.01,dist);
    //float alpha = sm*sm2;

    FragColor = color;
}