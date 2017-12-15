#ifndef TEXTURE_H
#define TEXTURE_H

namespace GameEngine {

	class Texture
	{

	public:
		Texture();
		virtual ~Texture();
		void Generate(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data);
		void Use() const;


		Texture(Texture const&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(Texture const&) = delete;
		Texture& operator=(Texture &&) = delete;

		void Release();

		unsigned int GetID() const;
	protected:
		unsigned int ID = -1;
		unsigned int Width, Height;

		unsigned int InternalFormat;
		unsigned int ImageFormat;
		unsigned int WrapS;
		unsigned int WrapT;
		unsigned int FilterMin;
		unsigned int FilterMax;
	};

}

#endif // !TEXTURE_H
