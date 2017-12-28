#pragma once 

#include <vector>
#include <Engine\Core\Entity.h>

namespace GameEngine
{
	class Renderer;
	class CameraComponent;

	class Scene {

	public:

		static Scene* CreateFromFile(const char* Path);
		virtual ~Scene();
		virtual void OnEnter();
		virtual void OnUpdate(float DeltaTime);
		virtual void OnRender(Renderer* Renderer);
		virtual void OnExit();

		void AddEntity(Entity* Entity);
		void RemoveEntity(Entity* Entity, bool DeleteEntity = false);

		CameraComponent* GetCamera() const;
		void SetCamera(CameraComponent* Camera);

	protected:
		CameraComponent* SceneCamera;
		std::vector<Entity*> Entities;
	};
}

