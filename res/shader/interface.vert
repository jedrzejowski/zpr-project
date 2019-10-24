#version 330 core
layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoord;

out vec2 TexCoord;

uniform mat3 model = mat3(1);

void main() {

    gl_Position = vec4(iPosition, 1.0f);

    TexCoord = iTexCoord;
}