#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 cameraPos;
uniform vec3 light;
uniform sampler2D ourTexture;

void main() {
	FragColor = texture(ourTexture, TexCoord);
}
