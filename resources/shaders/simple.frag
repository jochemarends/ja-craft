#version 330 core

out vec4 color;
uniform sampler2D tex;
uniform sampler2DArray atlas;

in attribs_t {
    vec3 position;
    vec3 texcoord;
} attribs;

void main() {
    color = texture(atlas, attribs.texcoord);
//    color = texture(tex, attribs.texcoord);
}