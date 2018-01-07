#pragma once 


#include <Engine\Utils\JSON\JSON.h>

namespace GameEngine
{

#define DeclareComponentFactory(Class) \
	public:\
	static Component* Instantiate();\
	static void Register();

#define ImplementComponentFactory(Class) \
		Component* Class::Instantiate()\
		{\
			return new Class();\
		}\
		\
		 void Class::Register()\
		{\
			ComponentFactory::GetInstance().Register(std::string(#Class), &Class::Instantiate);\
		}

	class Entity;
	class Renderer;

	class Component 
	{

	public:
		Component();

		virtual ~Component();

		virtual void OnInitialize();
		virtual void Deserialize(JSONObject& Data);//TODO:: Use own parser to be able to pass a const reference
		virtual void Update(float DeltaTime);
		virtual void Render(Renderer* Renderer);
		Entity* GetOwner() const;
		void SetOwner(Entity* Entity);
		void Destroy();
		bool IsDestroyed();
		bool IsInitialized();
		bool RequireRendering() const;
		bool RequireUpdate() const;
	protected:
		bool RenderingRequire = false;
		bool UpdateRequire = false;
	private:
		Entity* Owner;
		bool Destroyed = false;
		bool Initialized = false;
	};

	typedef Component* (*ComponentInstantiator)();


}

