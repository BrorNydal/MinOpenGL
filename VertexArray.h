#pragma once

#include "GL/glew.h"

class VertexArray
{
	unsigned int ID;

public:
	VertexArray();
	~VertexArray();

	void updateData(GLsizei stride);

	void bind();
	void unbind();
};
