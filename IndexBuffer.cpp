#include "IndexBuffer.h"



IndexBuffer::IndexBuffer()
	: ID(0)
{
	glGenBuffers(1, &ID);
}


IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, (GLuint*)ID);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::updateData(const unsigned int *data, unsigned int count)
{
	bind();

	mCount = count;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}
