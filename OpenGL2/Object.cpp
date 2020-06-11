#include "Object.h"
#include "Texture.h"

Object::Object()
{
	
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

//getters and setters

mat4x4 Object::getTransformationMatrix() const { 
	return mTransformationMatrix; 
}

vec3 Object::getPosition() const { return mTransformationMatrix.getTranslation(); }

void Object::setPosition(vec3 newPos) { mTransformationMatrix.setTranslation(newPos); }

Texture * Object::getTexture() const
{
	return mTexture;
}

