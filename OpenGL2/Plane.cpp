#include "Plane.h"



Plane::Plane()
{
	mTexture = new Texture("Resources/Textures/front.png");

	mVertices.push_back(Vertex(0, 0, 0,  0, 0, 0,	0, 0));
	mVertices.push_back(Vertex(1, 0, 0,  0, 0, 0,	1, 0));
	mVertices.push_back(Vertex(1, 0, -1, 0, 0, 0,	1, 1));
	mVertices.push_back(Vertex(0, 0, -1, 0, 0, 0,	0, 1));

	mIndices.push_back(0);
	mIndices.push_back(1);
	mIndices.push_back(2);

	mIndices.push_back(2);
	mIndices.push_back(3);
	mIndices.push_back(0);
}


Plane::~Plane()
{
}

void Plane::draw()
{
	mVertexArray.bind();
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, NULL);
}
