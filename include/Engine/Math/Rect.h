#pragma once

namespace GameEngine
{
	struct Rect {
		float x, y, width, height;

		Rect() :x(0), y(0), width(0), height(0) {}

		Rect(float _x, float _y, float _width, float _height) :x(_x), y(_y), width(_width), height(_height) {}

		inline static bool CheckOverlap(const Rect &one, const Rect &two)
		{

			bool collisionX = one.x + one.width >= two.x &&
				two.x + two.width >= one.x;
			bool collisionY = one.y + one.height >= two.y &&
				two.y + two.height >= one.y;

			return collisionX && collisionY;
		}

	};
}