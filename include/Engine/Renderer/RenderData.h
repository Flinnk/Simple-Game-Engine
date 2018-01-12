#pragma once
#include <Engine\Math\Vector2.h>
#include <Engine\Math\Vector3.h>
#include <Engine\Graphics\TextureAtlas.h>

namespace GameEngine
{

	struct DrawCall2D {
		TextureRegion Region;
		Vector3 Postion;
		Vector3 Scale;
		Vector3 Color;
		const Texture* Texture;
		int DrawCallIdentifier;
		int DrawWidth = 0;
		int DrawHeight = 0;
		bool UseTextureSize = true;

	};

}
