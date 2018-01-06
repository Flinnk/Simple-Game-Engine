#pragma once

#include <Engine\Math\Math.h>


namespace GameEngine {

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


