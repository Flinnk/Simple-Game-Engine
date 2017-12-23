#pragma once

#include <Engine\Math\Math.h>


namespace GameEngine {
	struct Rect {
		float x, y, width, height;

		Rect() :x(0), y(0), width(0), height(0) {}

		Rect(float _x, float _y, float _width, float _height) :x(_x), y(_y), width(_width), height(_height) {}

	};

	struct Circle {

		float x, y, radius;

		Circle() :x(0), y(0), radius(0) {}

		Circle(float _x, float _y, float _radius) :x(_x), y(_y), radius(_radius) {}
	};

	struct CollisionData {
		bool Hit = false;
		Vector2 DifferenceVector = Vector2(0, 0);
	};

	bool CheckCollision(const Rect &one, const Rect &two);
	CollisionData CheckCollision(const Circle &one, const Rect &two);

}


