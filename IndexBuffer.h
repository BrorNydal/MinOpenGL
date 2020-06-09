#pragma once

#include "GL/glew.h"

class IndexBuffer
{
private:
	unsigned int ID;
	unsigned int mCount;

public:
	IndexBuffer();
	~IndexBuffer();

	void bind();
	void unbind();

	void updateData(const unsigned int *data, unsigned int count);

	inline unsigned int getCount() const { return mCount; }
};

