#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_texcoord;

out attribs_t {
    vec3 position;
    vec3 texcoord;
} attribs;

uniform mat4 proj, view, model = mat4(1);

void main() {
    attribs.position = a_position;
    attribs.texcoord = a_texcoord;
    gl_Position = proj * view * model * vec4(a_position, 1);
}