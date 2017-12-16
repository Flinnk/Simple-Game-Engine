#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <Engine\Core\Component.h>

namespace GameEngine
{
	class Renderer;


	class Entity {
	public:
		Entity();
		virtual ~Entity();
		virtual void Update(float DeltaTime);
		virtual void Render(Renderer* Renderer);

		void Destroy();
		bool IsDestroyed();

		void AddComponent(Component* Component);
	private:
		std::vector<Component*> Components;
		bool Destroyed = false;
	};
}

#endif // !ENTITY_H
