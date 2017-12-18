#ifndef SCENE_COMPONENT_H
#define SCENE_COMPONENT_H

#include <Engine\Core\Component.h>
#include <Engine\Core\Transform.h>

namespace GameEngine
{
	class SceneComponent : public Component
	{
	public:
		Transform& GetTransform();
		Vector3 GetAbsolutePosition();
		Vector3 GetRelativePosition();
	private:
		Transform ComponentTransform;
	};
}


#endif // !SCENE_COMPONENT_H
