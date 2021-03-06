
#include <Engine/Graphics/Texture.h>
#include <Engine/Graphics/OpenGL.h>
#include <Engine\Math\Vector2.h>
namespace GameEngine {

	Texture::Texture()
		: Width(0), Height(0), InternalFormat(GL_RGB), ImageFormat(GL_RGB), WrapS(GL_REPEAT), WrapT(GL_REPEAT), FilterMin(GL_LINEAR), FilterMax(GL_LINEAR)
	{
	}

	Texture::~Texture() {

	}


	void Texture::Generate(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data)
	{
		GLCall(glGenTextures(1, &ID));

		Width = width;
		Height = height;

		if (channels == 1)
			InternalFormat = ImageFormat = GL_RED;
		else if (channels == 3)
			InternalFormat = ImageFormat = GL_RGB;
		else if (channels == 4)
			InternalFormat = ImageFormat = GL_RGBA;

		GLCall(glBindTexture(GL_TEXTURE_2D, ID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, ImageFormat, GL_UNSIGNED_BYTE, data));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMax));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture::Use() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, ID));
	}

	unsigned int Texture::GetID() const
	{
		return ID;
	}

	void Texture::Release()
	{
		GLCall(glDeleteTextures(1, &ID));
		ID = 0;
	}

	unsigned int Texture::GetWidth() const
	{
		return Width;
	}

	unsigned int Texture::GetHeight() const
	{
		return Height;
	}

	Vector2 Texture::GetSize()const
	{
		return Vector2(Width,Height);
	}


}