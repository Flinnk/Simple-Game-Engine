
#include "Texture.h"
#include <GL\glew.h>

namespace GameEngine {

	Texture::Texture()
		: Width(0), Height(0), InternalFormat(GL_RGB), ImageFormat(GL_RGB), WrapS(GL_REPEAT), WrapT(GL_REPEAT), FilterMin(GL_LINEAR), FilterMax(GL_LINEAR)
	{
	}

	void Texture::Generate(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
	{
		glGenTextures(1, &ID);

		Width = width;
		Height = height;

		if (channels == 1)
			InternalFormat = ImageFormat = GL_RED;
		else if (channels == 3)
			InternalFormat = ImageFormat = GL_RGB;
		else if (channels == 4)
			InternalFormat = ImageFormat = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, ImageFormat, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMax);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Use() const
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	unsigned int Texture::GetID() const
	{
		return ID;
	}

}