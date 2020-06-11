#include "VertexArray.h"



VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::updateData(GLsizei stride)
{
	bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(nullptr));

	//Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

	//UVs
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
}

void VertexArray::bind()
{
	glBindVertexArray(ID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
