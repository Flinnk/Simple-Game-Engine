#pragma once

#include <vector>
#include <Engine\Core\Component.h>
#include <Engine\Core\Transform.h>
#include <Engine\Utils\JSON\JSON.h>

namespace GameEngine
{

typedef Entity*(*EntityInstantiator)();

#define DeclareEntityFactory(Class) \
	public:\
	static Entity* Instantiate();\
	static void Register();

#define ImplementEntityFactory(Class) \
		Entity* Class::Instantiate()\
		{\
			return new Class();\
		}\
		\
		 void Class::Register()\
		{\
			EntityFactory::GetInstance().Register(std::string(#Class), &Class::Instantiate);\
		}

	class Renderer;
	class Scene;
	class SceneComponent;

	class Entity {
		friend class Scene;
		friend class EntityFactory;

		DeclareEntityFactory(Entity)

	public:
		Entity();
		virtual ~Entity();

		virtual void Deserialize(JSONObject& Data);//TODO:: Use own parser to be able to pass a const reference
		virtual void Update(float DeltaTime);
		void Render(Renderer* Renderer);


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

		Scene* GetScene() const;
	private:
		Scene* OwnerScene = nullptr;
		unsigned int ID = 0;

		void SetScene(Scene* Scene);

		std::vector<Component*> Components;
		std::vector<Entity*> Childs;
		Entity* Parent = nullptr;
		bool Destroyed = false;

		SceneComponent* TransformComponent;

	};


}
