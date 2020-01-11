#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
flat in uint TexNum;

uniform sampler2D gui_texture;
uniform sampler2D font_texture;
uniform sampler2D block_texture;

void main() {
    vec4 outColor;

    if (TexNum == uint(0)) {
        outColor = texture(block_texture, TexCoord);
    }

    if (TexNum == uint(1)) {
        outColor = texture(gui_texture, TexCoord);
    }

    if (TexNum == uint(2)) {
        outColor = texture(font_texture, TexCoord);
    }

    FragColor = outColor;
}
