#version 330 core
layout (location = 0) in vec3 aPos; // pos var has attrib pos 0
layout (location = 1) in float aOffset;

out vec3  vertexColor;
out float offset;

void main() {
    gl_Position = vec4(aPos, 1.0f);
    vertexColor = vec3(1.0f, 1.0f, 1.0f);
    offset = aOffset;
}
