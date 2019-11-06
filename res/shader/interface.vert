#version 330 core
layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoord;
layout (location = 3) in uint iTexNum;

out vec2 TexCoord;
flat out uint TexNum;

uniform mat4 model = mat4(1);

void main() {

    gl_Position = model * vec4(iPosition, 1.f);

    TexCoord = iTexCoord;
    TexNum = iTexNum;
}