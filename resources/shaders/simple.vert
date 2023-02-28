#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_pos;

out attribs_t {
    vec3 pos;
    vec2 tex_pos;
} attribs;

uniform mat4 proj, view, model;

void main() {
    attribs.pos = pos;
    attribs.tex_pos = tex_pos;
    gl_Position = proj * view * vec4(pos, 1);
}