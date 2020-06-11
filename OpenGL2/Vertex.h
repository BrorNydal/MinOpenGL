#pragma once

class Vertex
{
public:
	Vertex();
	Vertex(float X, float Y, float Z,
	float R = 0, float G = 0, float B = 0,
	float U = 0, float V = 0);
	~Vertex();

	//Position
	float x, y, z;
	//Normal
	float r, g, b;
	//Texture-Coordinate
	float u, v;	
};

