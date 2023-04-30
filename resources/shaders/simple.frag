#version 330 core

out vec4 color;
uniform sampler2D tex;

in attribs_t {
    vec3 position;
    vec2 texcoord;
} attribs;

void main() {
    color = texture(tex, attribs.texcoord);
}