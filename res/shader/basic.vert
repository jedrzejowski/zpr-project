#version 330 core
layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec3 iColor;
layout (location = 3) in vec2 iTexCoord;

out vec3 Color;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;


uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;

void main() {
    gl_Position = projection * camera * model * vec4(iPosition, 1.0f);

	FragPos = vec3(model * vec4(iPosition, 1.0));

    Normal = mat3(transpose(inverse(model))) * iNormal;

    Color = iColor;
    TexCoord = iTexCoord;
}