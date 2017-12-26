#include <Engine\Entities\EntityFactory.h>

namespace GameEngine
{


	EntityFactory& EntityFactory::GetInstance()
	{
		static EntityFactory Instance;
		return Instance;
	}

	bool EntityFactory::Register(const std::string& Class, Instantiator Function)
	{
		bool Result = false;

		if (FunctionPointers.find(Class) == FunctionPointers.end())
		{
			FunctionPointers[Class] = Function;
			Result = true;
		}

		return Result;
	}

	Entity* EntityFactory::Create(const std::string& Class)
	{
		Entity* NewEntity = nullptr;

		if (FunctionPointers.find(Class) != FunctionPointers.end())
		{
			Instantiator Function = FunctionPointers[Class];
			NewEntity = Function();
			NewEntity->ID = ID++;
		}

		return NewEntity;
	}


}