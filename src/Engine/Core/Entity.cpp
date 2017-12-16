#include <Engine\Core\Entity.h>


namespace GameEngine
{
	bool Entity::IsDestroyed()
	{
		return Destroyed;
	}

	Entity::Entity()
	{

	}

	Entity::~Entity()
	{

	}

	void Entity::Update(float DeltaTime)
	{
		std::vector<Component*>::iterator it = Components.begin();
		while (it != Components.end())
		{
			(*it)->Update(DeltaTime);
			++it;
		}
	}

	void Entity::Render(Renderer* Renderer) 
	{
		std::vector<Component*>::iterator it = Components.begin();
		while (it != Components.end())
		{
			(*it)->Render(Renderer);
			++it;
		}
	}

	void Entity::AddComponent(Component* Component)
	{
		Component->SetOwner(this);
		Components.push_back(Component);
	}


	void Entity::Destroy()
	{
		Destroyed = true;
	}
}