#version 130

in vec3 vertex;
in vec3 normal;

//out float lit;
out vec3 col;

uniform	mat4 mvp_mat;
uniform mat4 model_mat;

void main(void) {
	vec3 normal_w = vec3(model_mat * vec4(normal, 0));
	vec3 light_dir = normalize(vec3(1, 1, 1));

	col = normal;
	//lit = max(0, dot(normal_w, light_dir));
	gl_Position = mvp_mat * vec4(vertex, 1.f);
}
