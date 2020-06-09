#shader vertex
#version 410 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UV;

out vec3 _normal;

uniform mat4 tmatrix;
uniform mat4 vmatrix;
uniform mat4 pmatrix;

void main()
{
	_normal = normal;

	//gl_Position = vec4(position, 1);
	gl_Position = pmatrix * vmatrix * tmatrix * vec4(position, 1); 
};


#shader fragment
#version 410 core 

in vec3 _normal;

out vec4 fragColor;

void main()
{
	fragColor = vec4(_normal, 1);
};