#include <Engine\Core\Scene.h>

namespace GameEngine
{
	Scene::~Scene()
	{
		while (Entities.size() > 0)
		{
			Entity* Entity = Entities.back();
			Entities.pop_back();

			if (Entity)
				delete Entity;
			Entity = nullptr;
		}
	}

	void Scene::OnEnter()
	{

	}

	void Scene::OnUpdate(float DeltaTime)
	{
		std::vector<Entity*>::iterator it = Entities.begin();
		while (it != Entities.end())
		{
			(*it)->Update(DeltaTime);
			++it;
		}

		it = Entities.begin();
		while (it != Entities.end())
		{
			if ((*it)->IsDestroyed())
			{
				Entity* Entity = *it;
				it = Entities.erase(it);
				delete Entity;
			}
			else 
			{
				++it;
			}
		}
	}

	void Scene::OnRender(Renderer* Renderer)
	{
		std::vector<Entity*>::iterator it = Entities.begin();
		while (it != Entities.end())
		{
			(*it)->Render(Renderer);
			++it;
		}
	}

	void Scene::OnExit()
	{

	}

	void Scene::AddEntity(Entity* Entity)
	{
		Entities.push_back(Entity);
	}



}