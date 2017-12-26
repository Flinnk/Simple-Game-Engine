#pragma once

#include <string>
#include <Engine\Utils\JSON\JSON.h>

namespace GameEngine
{

	class Scene;
	class Entity;

	class SceneParser
	{
	public:
		static Scene* Parse(const char* Path);
	private:
		static bool ParseScene(Scene* WrittingScene, const JSONValue* Data);
		static bool ParseEntityChilds(Entity* ParseEntity, JSONObject& object);

	};
}