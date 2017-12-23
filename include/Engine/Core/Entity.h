#pragma once

#include <vector>
#include <Engine\Core\Component.h>
#include <Engine\Core\Transform.h>

namespace GameEngine
{
	class Renderer;
	class Scene;

	class Entity {
		friend class Scene;

	public:
		Entity();
		virtual ~Entity();
		virtual void Update(float DeltaTime);
		virtual void Render(Renderer* Renderer);

		void Destroy();
		bool IsDestroyed();

		void AddComponent(Component* Component);
		void RemoveComponent(Component* Component, bool DestroyComponent = false);

		void AddChild(Entity* Entity);
		void RemoveChild(Entity* Entity);

		Transform GetTransform();
		void SetTransform(const Transform& Value);

		Vector3 GetAbsolutePosition();
		Vector3 GetRelativePosition();
		void SetRelativePosition(const Vector3& Value);

		Vector3 GetAbsoluteRotation();
		Vector3 GetRelativeRotation();
		void SetRelativeRotation(const Vector3& Value);

		Vector3 GetAbsoluteScale();
		Vector3 GetRelativeScale();
		void SetRelativeScale(const Vector3& Value);
		

		void DetachFromParent();
	private:
		Scene* OwnerScene = nullptr;

		void SetScene(Scene* Scene);
		Transform EntityTransform;

		std::vector<Component*> Components;
		std::vector<Entity*> Childs;
		Entity* Parent = nullptr;
		bool Destroyed = false;

	};
}
