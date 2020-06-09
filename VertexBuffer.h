#pragma once

#include "GL/glew.h"

class VertexBuffer
{
	unsigned int ID;

public:
	VertexBuffer();
	~VertexBuffer();

	void bind();
	void unbind();

	void updateData(const void *data, unsigned int size);
};

