#ifndef COMPONENT_H
#define COMPONENT_H


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
	private:
		Entity* Owner;
	};
}

#endif // !COMPONENT_H
