#include "Texture.h"
#include <Vendor/stb_image/stb_image.h>
#include <string>



Texture::Texture()
{
}

Texture::Texture(std::string filePath)
{
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	mImage.data = stbi_load(filePath.c_str(), &mImage.width, &mImage.height, &mImage.channels, 0);

	if (mImage.data)
	{
		mImage.source = filePath;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mImage.width, mImage.height, 0, GL_RGB, GL_UNSIGNED_BYTE, mImage.data);
		glGenerateMipmap(GL_TEXTURE_2D);    //Generates different sizes of the texture depending on the distance we see the object from
	}
	else
		std::cout << "Could not load texture file:" + filePath << std::endl;

	stbi_image_free(mImage.data);
}


Texture::~Texture()
{
}

unsigned int Texture::getTextureID() const
{
	return mID;
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
