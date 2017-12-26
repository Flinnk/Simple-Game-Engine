#include <Engine\Core\Scene.h>
#include <Engine\Core\Engine.h>
#include <Engine\Math\Vector2.h>
#include <Engine\Components\CameraComponent.h>
#include <Engine\Renderer\Renderer.h>
#include <Engine\Entities\EntityFactory.h>
#include <Engine\Utils\JSON\JSON.h>
#include <Engine\Utils\File.h>
#include <Engine\Utils\SceneParser.h>
namespace GameEngine
{

	Scene* Scene::CreateFromFile(const char* Path)
	{
		Scene* FileScene = nullptr;
		FileScene = SceneParser::Parse(Path);
		return FileScene;
	}


	Scene::~Scene()
	{
		std::vector<Entity*> _Entities = Entities;
		std::vector<Entity*>::iterator entityIterator = _Entities.begin();
		while (entityIterator != _Entities.end())
		{
			Entity* Entity = *entityIterator;
			entityIterator = _Entities.erase(entityIterator);
			delete Entity;
		}
		Entities.clear();
	}

	void Scene::OnEnter()
	{

	}

	void Scene::OnUpdate(float DeltaTime)
	{
		std::vector<Entity*> _Entities = Entities;
		std::vector<Entity*>::iterator entityIterator = _Entities.begin();
		while (entityIterator != _Entities.end())
		{
			(*entityIterator)->Update(DeltaTime);
			++entityIterator;
		}
	}

	void Scene::OnRender(Renderer* Renderer)
	{
		if (SceneCamera)
		{
			Vector2 Size = Engine::GetInstance().GetDisplaySize();

			Renderer->SetCamera(SceneCamera);

			std::vector<Entity*> _Entities = Entities;
			std::vector<Entity*>::iterator it = _Entities.begin();
			while (it != _Entities.end())
			{
				(*it)->Render(Renderer);
				++it;
			}
		}
	}

	void Scene::OnExit()
	{

	}

	void Scene::AddEntity(Entity* Entity)
	{
		Entities.push_back(Entity);
		Entity->SetScene(this);
	}

	void Scene::RemoveEntity(Entity* EntityToRemove, bool DeleteEntity)
	{
		std::vector<Entity*>::iterator it = Entities.begin();
		bool found = false;
		while (it != Entities.end() && !found)
		{

			if ((*it) == EntityToRemove)
			{
				Entity* Entity = *it;
				it = Entities.erase(it);
				found = true;
				if (DeleteEntity)
					delete Entity;
			}
			else
			{
				++it;
			}
		}
	}

	CameraComponent* Scene::GetCamera() const
	{
		return SceneCamera;
	}


}