#pragma once

class Vertex
{
public:
	Vertex();
	Vertex(float X, float Y, float Z,
	float R, float G, float B,
	float U, float V);
	~Vertex();

	//Position
	float x, y, z;
	//Normal
	float r, g, b;
	//Texture-Coordinate
	float u, v;	
};

