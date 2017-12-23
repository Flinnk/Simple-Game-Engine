#pragma once 

namespace GameEngine
{
	class Entity;
	class Renderer;

	class Component 
	{

	public:
		Component();

		virtual ~Component();

		virtual void Update(float DeltaTime);
		virtual void Render(Renderer* Renderer);
		Entity* GetOwner();
		void SetOwner(Entity* Entity);
		void Destroy();
		bool IsDestroyed();
	private:
		Entity* Owner;
		bool Destroyed = false;
	};
}

