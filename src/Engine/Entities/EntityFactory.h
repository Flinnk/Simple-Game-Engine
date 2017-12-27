#pragma once
#include <map>
#include <Engine\Core\Entity.h>

namespace GameEngine
{
	class EntityFactory
	{
	public:
		static EntityFactory& GetInstance();
		Entity* Create(const std::string& Class);
		bool Register(const std::string& Class, EntityInstantiator Function);
	private:

		std::map<std::string, EntityInstantiator> FunctionPointers;
		unsigned int ID = 0;
	};
}