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

	Entity* Component::GetOwner() const
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

	void Component::Deserialize(JSONObject& Data)
	{

	}

	void Component::OnInitialize()
	{
		Initialized = true;
	}

	bool Component::IsInitialized()
	{
		return Initialized;
	}

	bool Component::RequireRendering() const
	{
		return RenderingRequire;
	}

	bool Component::RequireUpdate() const
	{
		return UpdateRequire;
	}

}