#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;

out attribs_t {
    vec3 position;
    vec2 texcoord;
} attribs;

uniform mat4 proj, view, model;

void main() {
    attribs.position = a_position;
    attribs.texcoord = a_texcoord;
    gl_Position = proj * view * vec4(a_position, 1);
}