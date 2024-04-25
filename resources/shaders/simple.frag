#version 330 core

out vec4 color;
in vec3 texcoord;
uniform sampler2DArray textures;

void main() {
    color = texture(textures, texcoord);
}
