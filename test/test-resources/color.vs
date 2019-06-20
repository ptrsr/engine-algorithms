#version 130

in vec3 vertex;
uniform	mat4 model_mat;
uniform	mat4 view_mat;
uniform	mat4 proj_mat;

void main(void)
{
	gl_Position = model_mat * view_mat * proj_mat * vec4(vertex, 1.f);
}
