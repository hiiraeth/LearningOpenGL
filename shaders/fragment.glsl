#version 330
in vec3 vertexColor;
in float offset;

out vec4 FragColor;

uniform vec3 ourColor;
uniform float uTime;
uniform float uSpeed;

void main() {
    float phase = uTime * uSpeed + offset;

    float alpha = (sin(phase) + 1.0) * 0.5;

    FragColor  = vec4(ourColor, alpha);
}
