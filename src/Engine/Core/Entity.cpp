#include <Engine\Core\Entity.h>
#include <Engine\Core\Scene.h>

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
		std::vector<Component*> _Components = Components;
		std::vector<Component*>::iterator componentIterator = _Components.begin();
		while (componentIterator != _Components.end())
		{
			(*componentIterator)->Update(DeltaTime);
			++componentIterator;
		}

		std::vector<Entity*> _Childs = Childs;
		std::vector<Entity*>::iterator childIterator = _Childs.begin();
		while (childIterator != _Childs.end())
		{
			(*childIterator)->Update(DeltaTime);
			++childIterator;
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


		std::vector<Entity*> _Childs = Childs;
		std::vector<Entity*>::iterator childIterator = _Childs.begin();
		while (childIterator != _Childs.end())
		{
			(*childIterator)->Render(Renderer);
			++childIterator;
		}
	}

	void Entity::AddComponent(Component* Component)
	{
		Component->SetOwner(this);
		Components.push_back(Component);
	}

	void Entity::RemoveComponent(Component* ComponentToRemove, bool DestroyComponent)
	{
		std::vector<Component*>::iterator it = Components.begin();
		bool found = false;
		while (it != Components.end() && !found)
		{

			if ((*it) == ComponentToRemove)
			{
				Component* Component = *it;
				it = Components.erase(it);
				if (DestroyComponent)
					delete Component;
				found = true;
			}
			else
			{
				++it;
			}
		}
	}

	void Entity::AddChild(Entity* Entity)
	{
		Childs.push_back(Entity);
		Entity->Parent = this;
		Entity->EntityTransform.Position = this->GetAbsolutePosition()*-1;

		if (OwnerScene)
			OwnerScene->RemoveEntity(Entity);
	}

	void Entity::RemoveChild(Entity* EntityToRemove)
	{
		Entity* RemovedEntity = nullptr;
		std::vector<Entity*>::iterator it = Childs.begin();
		bool found = false;
		while (it != Childs.end() && !found)
		{

			if ((*it) == EntityToRemove)
			{
				RemovedEntity = *it;
				it = Childs.erase(it);
				found = true;
				RemovedEntity->EntityTransform.Position = RemovedEntity->GetAbsolutePosition();
				RemovedEntity->Parent = nullptr;

				if (OwnerScene)
				{
					OwnerScene->AddEntity(RemovedEntity);
				}
				//delete Entity;
			}
			else
			{
				++it;
			}
		}
	}

	void Entity::DetachFromParent()
	{
		if (Parent)
			Parent->RemoveChild(this);
	}


	void Entity::Destroy()
	{
		Destroyed = true;
		DetachFromParent();
		if (OwnerScene)
			OwnerScene->RemoveEntity(this, true);
	}

	Transform& Entity::GetTransform()
	{
		return EntityTransform;
	}

	Vector3 Entity::GetAbsolutePosition()
	{
		if (Parent)
		{
			return (Parent->GetAbsolutePosition() + EntityTransform.Position);
		}
		else
		{
			return EntityTransform.Position;
		}
	}

	Vector3 Entity::GetRelativePosition()
	{
		return EntityTransform.Position;
	}

	void Entity::SetScene(Scene* Scene)
	{
		OwnerScene = Scene;
	}

}