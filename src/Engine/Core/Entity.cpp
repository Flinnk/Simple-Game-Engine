#include <Engine\Core\Entity.h>
#include <Engine\Core\Scene.h>
#include <Engine\Entities\EntityFactory.h>
#include <Engine\Components\SceneComponent.h>
namespace GameEngine
{
	ImplementEntityFactory(Entity)

		bool Entity::IsDestroyed()
	{
		return Destroyed;
	}

	Entity::Entity()
	{
		TransformComponent = new SceneComponent();
		AddComponent(TransformComponent);
	}

	Entity::~Entity()
	{
		std::vector<Component*> _Components = Components;
		std::vector<Component*>::iterator componentIterator = _Components.begin();
		while (componentIterator != _Components.end())
		{
			Component* Component = *componentIterator;
			componentIterator = _Components.erase(componentIterator);
			delete Component;
		}
		Components.clear();

		std::vector<Entity*> _Childs = Childs;
		std::vector<Entity*>::iterator entityIterator = _Childs.begin();
		while (entityIterator != _Childs.end())
		{
			Entity* Entity = *entityIterator;
			entityIterator = _Childs.erase(entityIterator);
			delete Entity;
		}
		Childs.clear();
	}

	void Entity::Update(float DeltaTime)
	{
		std::vector<Component*> _Components(Components.begin(),Components.end());
		std::vector<Component*>::iterator componentIterator = _Components.begin();
		while (componentIterator != _Components.end())
		{
			if ((*componentIterator)->RequireUpdate())
				(*componentIterator)->Update(DeltaTime);
			++componentIterator;
		}

		std::vector<Entity*> _Childs(Childs.begin(), Childs.end());
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
			if ((*it)->RequireRendering())
				(*it)->Render(Renderer);
			++it;
		}


		std::vector<Entity*>::iterator childIterator = Childs.begin();
		while (childIterator != Childs.end())
		{
			(*childIterator)->Render(Renderer);
			++childIterator;
		}
	}

	void Entity::AddComponent(Component* Component)
	{
		Component->SetOwner(this);
		Components.push_back(Component);
		if (OwnerScene && !Component->IsInitialized())
			Component->OnInitialize();
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
		if (Entity->TransformComponent)
			Entity->TransformComponent->SetRelativePosition(this->GetAbsolutePosition()*-1);
		Entity->OwnerScene = OwnerScene;//Added for deserialization 

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
				if (RemovedEntity->TransformComponent)
					RemovedEntity->TransformComponent->SetRelativePosition(RemovedEntity->GetAbsolutePosition());
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

	Transform Entity::GetTransform()
	{
		return TransformComponent ? TransformComponent->GetTransform() : Transform();
	}

	void Entity::SetTransform(const Transform& Value)
	{
		if (TransformComponent)
			TransformComponent->SetTransform(Value);
	}


	Vector3 Entity::GetAbsolutePosition()
	{
		if (Parent)
		{
			return (Parent->GetAbsolutePosition() + GetTransform().Position);
		}
		else
		{
			return GetTransform().Position;
		}
	}

	Vector3 Entity::GetRelativePosition()
	{
		return GetTransform().Position;
	}



	void Entity::SetRelativePosition(const Vector3& Value)
	{
		if (TransformComponent)
			TransformComponent->SetRelativePosition(Value);
	}

	Vector3 Entity::GetAbsoluteRotation()
	{
		if (Parent)
		{
			return (Parent->GetAbsoluteRotation() + GetTransform().Rotation);
		}
		else
		{
			return GetTransform().Rotation;
		}
	}

	Vector3 Entity::GetRelativeRotation()
	{
		return GetTransform().Rotation;
	}

	void Entity::SetRelativeRotation(const Vector3& Value)
	{
		if (TransformComponent)
			TransformComponent->SetRelativeRotation(Value);
	}

	Vector3 Entity::GetAbsoluteScale()
	{
		if (Parent)
		{
			return (Parent->GetAbsoluteScale() * GetTransform().Scale);
		}
		else
		{
			return GetTransform().Scale;
		}
	}

	Vector3 Entity::GetRelativeScale()
	{
		return GetTransform().Scale;
	}

	void Entity::SetRelativeScale(const Vector3& Value)
	{
		if (TransformComponent)
			TransformComponent->SetRelativeScale(Value);
	}

	void Entity::SetScene(Scene* Scene)
	{
		OwnerScene = Scene;
		for (Component* component : Components)
		{
			if (!component->IsInitialized())
				component->OnInitialize();
		}
	}

	Scene* Entity::GetScene() const
	{
		return OwnerScene;
	}


	void Entity::Deserialize(JSONObject& Data)
	{
		if (TransformComponent)
			TransformComponent->Deserialize(Data);
	}



}