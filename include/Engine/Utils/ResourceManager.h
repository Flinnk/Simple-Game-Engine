#pragma once 

#include <map>
#include <string>
#include <Engine\Graphics\Shader.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\Graphics\Mesh.h>

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

		const Mesh* LoadMesh(std::string Path, std::string ResourceID);
		const Mesh* GetMesh(std::string ResourceID);

		void Clear();

		std::string GetResourceDirectory();

	private:
		ResourceManager();

		std::map<std::string, Shader*> Shaders;
		std::map<std::string, Texture*> Textures;
		std::map<std::string, Mesh*> Meshes;

		std::string ResourceDirectory;

	};
}


