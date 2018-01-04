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

		Shader* LoadShader(std::string& VertexSourceCode, std::string& FragmentSourceCode, std::string& ResourceID);
		Shader* GetShader(std::string& ResourceID);

		const Texture* LoadTexture(const char* ResourceRelativePath);
		const Texture* GetTexture(const char* ResourceRelativePath);

		const Mesh* LoadMesh(const char* ResourceRelativePath);
		const Mesh* GetMesh(const char* ResourceRelativePath);

		void Clear();

		std::string& GetResourceDirectory();

		void MountResourceDirectory(std::string RootDirectory);

	private:
		ResourceManager();

		std::map<std::string, Shader*> Shaders;
		std::map<std::string, Texture*> Textures;
		std::map<std::string, Mesh*> Meshes;

		std::string ResourceDirectory;

	};
}


