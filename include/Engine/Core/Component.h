#pragma once 


#include <Engine\Utils\JSON\JSON.h>

namespace GameEngine
{
	class Entity;
	class Renderer;

	class Component 
	{

	public:
		Component();

		virtual ~Component();

		virtual void Deserialize(JSONObject& Data);//TODO:: Use own parser to be able to pass a const reference
		virtual void Update(float DeltaTime);
		virtual void Render(Renderer* Renderer);
		Entity* GetOwner() const;
		void SetOwner(Entity* Entity);
		void Destroy();
		bool IsDestroyed();
	private:
		Entity* Owner;
		bool Destroyed = false;
	};

	typedef Component* (*ComponentInstantiator)();

#define RegisterComponentFactory(Class) \
	static Component* Instantiate()\
	{\
		return new Class();\
	}\
	\
	static bool Result = ComponentFactory::GetInstance().Register(std::string(#Class),&Instantiate);
}

