#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_texcoord;

out vec3 texcoord;

uniform mat4 proj  = mat4(1);
uniform mat4 view  = mat4(1);
uniform mat4 model = mat4(1);

void main() {
    texcoord = a_texcoord;
    gl_Position = proj * view * model * vec4(a_position, 1);
}

