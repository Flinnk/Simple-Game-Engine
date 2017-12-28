#pragma once
#include <map>
#include <Engine\Core\Component.h>
namespace GameEngine
{
	class ComponentFactory {
	public:
		static ComponentFactory& GetInstance();
		Component* Create(const std::string& Class);
		bool Register(const std::string& Class, ComponentInstantiator Function);
	private:
		std::map<std::string, ComponentInstantiator> FunctionPointers;
	};
}