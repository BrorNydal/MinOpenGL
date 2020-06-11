#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UV;

out vec2 _UV;

uniform mat4 tmatrix;
uniform mat4 vmatrix;
uniform mat4 pmatrix;

void main()
{
	_UV = UV;

	gl_Position = pmatrix * vmatrix * tmatrix * vec4(position, 1);
};


#shader fragment
#version 410 core

uniform sampler2D textureSampler;

in vec2 _UV;

out vec4 fragColor;

void main()
{
	kk
	fragColor = texture(textureSampler, _UV);
};