#version 130

//in float lit;
in vec3 col;

void main(void) {
	gl_FragColor = vec4(col, 1);
}
