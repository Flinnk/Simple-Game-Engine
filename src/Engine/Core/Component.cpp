#include <Engine\Core\Component.h>
#include <Engine\Core\Entity.h>

namespace GameEngine
{
	Component::Component()
	{

	}

	Component::~Component()
	{
		Owner = nullptr;
	}

	void Component::Update(float DeltaTime)
	{

	}
	void Component::Render(Renderer* Renderer)
	{

	}

	Entity* Component::GetOwner()
	{
		return Owner;
	}

	void Component::SetOwner(Entity* Entity)
	{
		Owner = Entity;
	}

	void Component::Destroy()
	{
		Destroyed = true;
		if (Owner)
			Owner->RemoveComponent(this,true);
	}

	bool Component::IsDestroyed()
	{
		return Destroyed;
	}
}