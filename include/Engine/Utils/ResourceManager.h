#pragma once 

#include <map>
#include <string>
#include <Engine\Graphics\Shader.h>
#include <Engine\Graphics\Texture.h>
#include <Engine\Graphics\Mesh.h>
#include <Engine\Graphics\TextureAtlas.h>
namespace GameEngine
{
	struct ShaderSource;

	class ResourceManager
	{
	public:
		~ResourceManager();


		ResourceManager(ResourceManager const&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(ResourceManager const&) = delete;
		ResourceManager& operator=(ResourceManager &&) = delete;

		static ResourceManager& GetInstance();

		Shader* LoadShader(const char* ResourceRelativePath);
		Shader* GetShader(const char* ResourceRelativePath);

		const Texture* LoadTexture(const char* ResourceRelativePath);
		const Texture* GetTexture(const char* ResourceRelativePath);

		const TextureAtlas* LoadTextureAtlas(const char* ResourceRelativePath);
		const TextureAtlas* LoadTextureAtlas(const char* ResourceRelativePath, Vector2 size, int columns, int elements);
		const TextureAtlas* GetTextureAtlas(const char* ResourceRelativePath);

		const Mesh* LoadMesh(const char* ResourceRelativePath);
		const Mesh* GetMesh(const char* ResourceRelativePath);

		void Clear();

		std::string& GetResourceDirectory();

		void MountResourceDirectory(std::string RootDirectory);

	private:
		ResourceManager();
		ShaderSource ParseShader(const char* Path);


		std::map<std::string, Shader*> Shaders;
		std::map<std::string, Texture*> Textures;
		std::map<std::string, TextureAtlas*> TextureAtlases;

		std::map<std::string, Mesh*> Meshes;

		std::string ResourceDirectory;

	};
}


