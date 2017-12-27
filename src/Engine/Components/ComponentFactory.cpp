#include <Engine\Components\ComponentFactory.h>

namespace GameEngine
{


	ComponentFactory& ComponentFactory::GetInstance()
	{
		static ComponentFactory Instance;
		return Instance;
	}

	bool ComponentFactory::Register(const std::string& Class, ComponentInstantiator Function)
	{
		bool Result = false;

		if (FunctionPointers.find(Class) == FunctionPointers.end())
		{
			FunctionPointers[Class] = Function;
			Result = true;
		}

		return Result;
	}

	Component* ComponentFactory::Create(const std::string& Class)
	{
		Component* NewEntity = nullptr;

		if (FunctionPointers.find(Class) != FunctionPointers.end())
		{
			ComponentInstantiator Function = FunctionPointers[Class];
			NewEntity = Function();
		}

		return NewEntity;
	}


}