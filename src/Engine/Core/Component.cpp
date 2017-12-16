#include <Engine\Core\Component.h>

namespace GameEngine
{
	Component::Component()
	{

	}

	Component::~Component()
	{

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
}