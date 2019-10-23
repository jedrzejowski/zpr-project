#version 330 core
layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoord;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 chunkPos = mat4(1);

void main() {

    vec4 pos = model * chunkPos * vec4(iPosition, 1.0f);

    gl_Position = projection * camera * pos;

    FragPos = vec3(pos);

    Normal = mat3(transpose(inverse(model))) * iNormal;

    TexCoord = iTexCoord;
}