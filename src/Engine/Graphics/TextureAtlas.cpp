#include <Engine\Graphics\TextureAtlas.h>
#include <Engine\Math\Vector2.h>
#include <Engine\Graphics\Texture.h>
namespace GameEngine
{
	TextureAtlas::TextureAtlas() :SourceTexture(nullptr), Columns(1), Elements(1) {}


	void TextureAtlas::Build(const Texture* texture)
	{
		Vector2 size;
		if (texture)
		{
			size.x = texture->GetWidth();
			size.y = texture->GetHeight();
		}

		Build(texture, size, 1, 1);
	}

	void TextureAtlas::Build(const Texture* texture, Vector2 Size, int columns, int elements)
	{
		SourceTexture = texture;
		Columns = columns;
		Elements = elements;

		if (!texture)
		{
			TextureRegion region;
			region.x = 0.0f;
			region.y = 0.0f;
			region.width = 1.0f;
			region.height = 1.0f;
			return;
		}

		Regions.reserve(elements);

		int column = 0;
		int row = 0;
		float textureWidth = texture->GetWidth();
		float textureHeight = texture->GetHeight();

		int i = 0;
		while (i < Elements)
		{
			column = i%Columns;

			TextureRegion region;
			region.x = (Size.x*column) / textureWidth;
			region.y = ((Size.y*row) / textureHeight);
			region.width = region.x + (Size.x / textureWidth);
			region.height = (region.y + (Size.y / textureHeight));

			++i;
			if (column > 0 && i%Columns == 0)
				++row;

			Regions.push_back(region);
		}
	}

	TextureAtlas::~TextureAtlas()
	{

	}

	void TextureAtlas::Release()
	{

	}

	const Texture* TextureAtlas::GetTexture() const
	{
		return SourceTexture;
	}

	const TextureRegion& TextureAtlas::GetTextureRegion(unsigned int index)const
	{
		return index < Elements ? Regions[index] : Regions[Elements - 1];
	}

	unsigned int TextureAtlas::RegionsNum()const
	{
		return Regions.size();
	}



}