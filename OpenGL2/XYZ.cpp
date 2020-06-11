#include "XYZ.h"



XYZ::XYZ()
{
	mVertices.push_back(Vertex(0, 0, 0, 1, 0, 0, 0, 0));
	mVertices.push_back(Vertex(1, 0, 0, 1, 0, 0, 0, 0));
	mVertices.push_back(Vertex(0, 0, 0, 0, 1, 0, 0, 0));
	mVertices.push_back(Vertex(0, 1, 0, 0, 1, 0, 0, 0));
	mVertices.push_back(Vertex(0, 0, 0, 0, 0, 1, 0, 0));
	mVertices.push_back(Vertex(0, 0, 1, 0, 0, 1, 0, 0));
}


XYZ::~XYZ()
{
}

void XYZ::draw()
{
	mVertexArray.bind();
	glDrawArrays(GL_LINES, 0, mVertices.size());
}
