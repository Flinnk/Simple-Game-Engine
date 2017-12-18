#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <Engine\Core\Entity.h>

namespace GameEngine
{
	class Renderer;

	class Scene {

	public:

		virtual ~Scene();
		virtual void OnEnter();
		virtual void OnUpdate(float DeltaTime);
		virtual void OnRender(Renderer* Renderer);
		virtual void OnExit();

		void AddEntity(Entity* Entity);
		void RemoveEntity(Entity* Entity, bool DeleteEntity = false);
	protected:
		std::vector<Entity*> Entities;
	};
}


#endif// !SCENE_H