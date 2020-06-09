#include "Object.h"

Object::Object()
{
	//TEST

	mVertices.push_back(Vertex(0,0,0,	1, 0, 0,	0, 0));
	mVertices.push_back(Vertex(1,0,0,	1, 0, 0,	0, 0));
	mVertices.push_back(Vertex(0,0,0,	0, 1, 0,	0, 0));
	mVertices.push_back(Vertex(0,1,0,	0, 1, 0,	0, 0));
	mVertices.push_back(Vertex(0,0,0,	0, 0, 1,	0, 0));
	mVertices.push_back(Vertex(0,0,1,	0, 0, 1,	0, 0));

	
}


Object::~Object()
{
}

void Object::initialize()
{
	mVertexBuffer.updateData(mVertices.data(), static_cast<unsigned int>(mVertices.size() * sizeof(Vertex)));
	mVertexArray.updateData(sizeof(Vertex));
	mIndexBuffer.updateData(mIndices.data(), static_cast<unsigned int>(mIndices.size()));

}

void Object::draw()
{
	mVertexArray.bind();

	glDrawArrays(GL_LINES, 0, mVertices.size());
	//glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, NULL);
}

void Object::rotate(float angle, vec3 axis)
{
	mTransformationMatrix.rotate(angle, axis);
}

void Object::rotate(float angle, float x, float y, float z)
{
	rotate(angle, vec3(x, y, z));
}

void Object::translate(vec3 translation)
{
	mTransformationMatrix.translate(translation);
}

void Object::translate(float x, float y, float z)
{
	translate(vec3(x, y, z));
}
