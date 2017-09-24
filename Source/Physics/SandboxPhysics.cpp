#include "SandboxPhysics.h"
#include "..\Math\Math.h"

namespace GameEngine {

	bool CheckCollision(const Rect &one, const Rect &two)
	{
		bool collisionX = one.x + one.width >= two.x &&
			two.x + two.width >= one.x;
		bool collisionY = one.y + one.height >= two.y &&
			two.y + two.height >= one.y;

		return collisionX && collisionY;
	}

	CollisionData CheckCollision(const Circle &one, const Rect &two)
	{
		CollisionData result;
		Vector2 center(Vector2(one.x, one.y) + one.radius);

		Vector2 aabb_half_extents(two.width / 2, two.height / 2);
		Vector2 aabb_center(
			two.x + aabb_half_extents.x,
			two.y + aabb_half_extents.y
		);

		Vector2 difference = center - aabb_center;
		Vector2 clamped = Vector2::Clamp(difference, -aabb_half_extents, aabb_half_extents);

		Vector2 closest = aabb_center + clamped;

		difference = closest - center;
		if (difference.Length() < one.radius) {
			result.Hit = true;
			result.DifferenceVector = difference;
		}
		else 
		{
			result.Hit = false;
			result.DifferenceVector = Vector2(0,0);
		}

		return result;
	}
}