#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
flat in uint TexNum;

uniform sampler2D guiTexture;
uniform sampler2D fontTexture;
uniform sampler2D blockTexture;

void main() {
    vec4 outColor;

    if (TexNum == uint(0)) {
        outColor = texture(guiTexture, TexCoord);
    }

    if (TexNum == uint(1)) {
        outColor = texture(fontTexture, TexCoord);
    }

    if (TexNum == uint(2)) {
        outColor = texture(blockTexture, TexCoord);
    }

    FragColor = outColor;
}
