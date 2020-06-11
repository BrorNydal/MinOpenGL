#include "VertexBuffer.h"




VertexBuffer::VertexBuffer()
	: ID(0)
{
	glGenBuffers(1, &ID);
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, (unsigned int*)ID);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::updateData(const void *data, unsigned int size)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
