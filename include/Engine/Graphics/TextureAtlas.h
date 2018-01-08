#pragma once 

#include <Engine\Math\Rect.h>
#include <vector>
namespace GameEngine
{
	class Texture;
	struct Vector2;

	using TextureRegion = Rect;

	class TextureAtlas {

	public:
		TextureAtlas();
		~TextureAtlas();
		void Release();

		void Build(const Texture* texture);
		void Build(const Texture* texture, Vector2 size, int columns, int elements);

		TextureAtlas(TextureAtlas const&) = delete;
		TextureAtlas(TextureAtlas&&) = delete;
		TextureAtlas& operator=(TextureAtlas const&) = delete;
		TextureAtlas& operator=(TextureAtlas &&) = delete;

		const Texture* GetTexture() const;
		const TextureRegion& GetTextureRegion(unsigned int index)const;
		unsigned int RegionsNum()const;

	private:
		std::vector<TextureRegion> Regions;

		const Texture* SourceTexture;

		unsigned int Columns;
		unsigned int Elements;
	};

}