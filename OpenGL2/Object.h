#pragma once

#include <iostream>
#include <vector>

//custom
#include "Vertex.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"

//custom math
#include "vec2.h"
#include "vec3.h"
#include "mat4x4.h"

class Object
{
private:
	vec3 mPosition;
	mat4x4 mTransformationMatrix;

public:
	Object();
	~Object();

	virtual void initialize();
	virtual void draw();

	//transformation
	void rotate(float angle, vec3 axis);
	void rotate(float angle, float x, float y, float z);

	void translate(vec3 translation);
	void translate(float x, float y, float z);

	//getters and setters
	mat4x4 getTransformationMatrix() const;
	vec3   getPosition()			 const;
	void   setPosition(vec3 newPos);

	Texture *getTexture() const;
protected:
	IndexBuffer mIndexBuffer;
	VertexArray mVertexArray;
	VertexBuffer mVertexBuffer;

	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;

	Texture *mTexture;
};

