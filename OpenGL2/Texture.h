#pragma once

#include <GL/glew.h>
#include <iostream>

struct Image {
	unsigned char *data;
	std::string source;
	int width, height;
	int channels;
};

class Texture
{
private://variables
	unsigned int mID;
	Image mImage;

public:
	Texture();
	Texture(std::string filePath);
	~Texture();

	unsigned int getTextureID() const;

	void bind(unsigned int slot = 0) const;
	void unbind() const;
};

