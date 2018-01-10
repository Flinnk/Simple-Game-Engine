#pragma once
#include <Engine\Math\Vector2.h>
#include <Engine\Math\Vector3.h>
#include <Engine\Graphics\TextureAtlas.h>

namespace GameEngine
{

	struct DrawCall2D {
		int DrawCallIdentifier;
		const Texture* Texture;
		TextureRegion Region;
		Vector3 Postion;
		Vector3 Scale;
		Vector3 Color;
	};

}
