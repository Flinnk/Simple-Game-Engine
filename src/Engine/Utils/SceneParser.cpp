#include <Engine\Utils\SceneParser.h>
#include <Engine\Core\Scene.h>
#include <Engine\Utils\File.h>
#include <Engine\Utils\JSON\JSON.h>
#include <Engine\Entities\EntityFactory.h>

namespace GameEngine
{

	Scene* SceneParser::Parse(const char * Path)
	{
		Scene* LoadScene = nullptr;

		std::string FileContent = File::ReadFile(Path);
		if (!FileContent.empty())
		{
			JSONValue* Value = JSON::Parse(FileContent.c_str());
			if (Value)
			{
				LoadScene = new Scene();
				if (!ParseScene(LoadScene, Value))
				{
					delete LoadScene;
					LoadScene = nullptr;
				}
				delete Value;
			}
		}


		return LoadScene;
	}

	bool SceneParser::ParseScene(Scene* WrittingScene, const JSONValue* Data)
	{
		JSONObject root;
		if (!Data->IsObject())
			return false;

		root = Data->AsObject();

		if (root.find(L"Scene") == root.end() || !root[L"Scene"]->IsObject())
			return false;

		JSONObject scene = root[L"Scene"]->AsObject();

		if (scene.find(L"Objects") == scene.end() || !scene[L"Objects"]->IsArray())
			return false;

		JSONArray objects = scene[L"Objects"]->AsArray();
		for (int i = 0; i < objects.size(); ++i)
		{
			JSONValue* value = objects[i];
			if (!value->IsObject())
				continue;

			JSONObject object = value->AsObject();

			if (object.find(L"Class") == object.end() || !object[L"Class"]->IsString())
				return false;


			std::wstring className = object[L"Class"]->AsString();
			Entity* newEntity = EntityFactory::GetInstance().Create(std::string(className.begin(), className.end()));//TODO: Use wide strings in the future
			if (!newEntity)
				return false;

			newEntity->Deserialize(object);
			WrittingScene->AddEntity(newEntity);

			if (!ParseEntityChilds(newEntity, object))
				return false;



		}

		return true;
	}

	bool SceneParser::ParseEntityChilds(Entity* ParseEntity, JSONObject& object)
	{
		if (object.find(L"Childs") != object.end() && object[L"Childs"]->IsArray())
		{
			JSONArray childs = object[L"Childs"]->AsArray();

			for (int i = 0; i < childs.size(); ++i)
			{
				JSONValue* value = childs[i];
				if (!value->IsObject())
					continue;

				JSONObject child = value->AsObject();
				if (child.find(L"Class") == child.end() || !child[L"Class"]->IsString())
					return false;


				std::wstring className = child[L"Class"]->AsString();
				Entity* newEntity = EntityFactory::GetInstance().Create(std::string(className.begin(), className.end()));//TODO: Use wide strings in the future
				if (!newEntity)
					return false;

				newEntity->Deserialize(child);

				ParseEntity->AddChild(newEntity);

				ParseEntityChilds(ParseEntity, child);

			}
		}

		return true;
	}


}
