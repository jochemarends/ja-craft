#version 330 core

out vec4 color;
uniform sampler2D tex;

in attribs_t {
    vec3 pos;
    vec2 tex_pos;
} attribs;

void main() {
    color = texture(tex, attribs.tex_pos);
}