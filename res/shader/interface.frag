#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
flat in uint TexNum;

uniform sampler2D guiTexture;
uniform sampler2D fontTexture;

void main() {
    if (TexNum == uint(0)) {
        FragColor = texture(guiTexture, TexCoord);
        return;
    }

    if (TexNum == uint(1)) {
        FragColor = texture(fontTexture, TexCoord);
        return;
    }
}
