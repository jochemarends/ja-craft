#version 330 core

out vec4 color;

in attribs_t {
    vec3 pos;
    vec3 tex_pos;
} attribs;

void main() {
    color = vec4(0, 1, 1, 1);
}