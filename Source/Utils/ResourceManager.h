
#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <map>
#include <string>
#include "..\Renderer\Shader.h"
#include "..\Renderer\Texture.h"

namespace GameEngine
{

	class ResourceManager
	{
	public:
		~ResourceManager();


		ResourceManager(ResourceManager const&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(ResourceManager const&) = delete;
		ResourceManager& operator=(ResourceManager &&) = delete;

		static ResourceManager& GetInstance();

		Shader* LoadShader(std::string VertexSourceCode, std::string FragmentSourceCode, std::string ResourceID);
		Shader* GetShader(std::string ResourceID);

		const Texture* LoadTexture(std::string Path, std::string ResourceID);
		const Texture* GetTexture(std::string ResourceID);

		void Clear();

	private:
		ResourceManager();

		std::map<std::string, Shader*> Shaders;
		std::map<std::string, Texture*> Textures;

	};
}
#endif // !RESOURCE_MANAGER


