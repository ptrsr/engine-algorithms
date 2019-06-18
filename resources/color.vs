#version 130

in vec3 vertex;

uniform	mat4 mvp;

void main(void) {
	gl_Position = mvp * vec4(vertex, 1.f);
}
