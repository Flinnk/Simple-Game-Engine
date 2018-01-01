

#include <Engine\Utils\ResourceManager.h>
#include <map>
#include <stb_image.h>
#include <Engine\Utils\File.h>
#include <Engine\Utils\MeshLoader.h>

namespace GameEngine
{
	ResourceManager::ResourceManager() 
	{
		std::string& ExecutionDirectory = File::GetExecutionDirectory();
		ResourceDirectory = ExecutionDirectory.substr(0,ExecutionDirectory.find_last_of("\\")) + "\\Resources\\";
	}
	ResourceManager::~ResourceManager() 
	{
		Clear();
	}


	ResourceManager& ResourceManager::GetInstance()
	{
		static ResourceManager Instance;
		return Instance;
	}

	Shader* ResourceManager::LoadShader(std::string& VertexSourceCode, std::string& FragmentSourceCode, std::string& ResourceID)//TODO: Use path instead of provided string as id?
	{
		if (Shaders.find(ResourceID) == Shaders.end())//Not found
		{
			Shader* shader = new Shader();
			if (shader->Compile(VertexSourceCode.c_str(), FragmentSourceCode.c_str()))
			{

				Shaders[ResourceID] = shader;
				return Shaders[ResourceID];
			}
			else
			{
				delete shader;
				shader = nullptr;
			}
			return shader;
		}
		else
		{
			return GetShader(ResourceID);
		}
	}

	Shader* ResourceManager::GetShader(std::string& ResourceID)
	{
		if (Shaders.find(ResourceID) == Shaders.end())//Not found
			return nullptr;
		return Shaders[ResourceID];
	}


	const Texture* ResourceManager::LoadTexture(std::string& Path, std::string& ResourceID)
	{
		if (Textures.find(ResourceID) == Textures.end())//Not found
		{
			Texture* LoadTexture = nullptr;

			int Width, Height, NrChannels;
			stbi_set_flip_vertically_on_load(false);
			unsigned char *Image = stbi_load(Path.c_str(), &Width, &Height, &NrChannels, 0);
			if (Image)
			{
				LoadTexture = new Texture();
				LoadTexture->Generate(Width, Height, NrChannels, Image);
				Textures[ResourceID] = LoadTexture;
			}

			stbi_image_free(Image);
			return LoadTexture;
		}
		else 
		{
			return GetTexture(ResourceID);
		}
	}

	const Texture* ResourceManager::GetTexture(std::string& ResourceID)
	{
		if (Textures.find(ResourceID) == Textures.end())//Not found
			return nullptr;
		return Textures[ResourceID];
	}

	const Mesh* ResourceManager::LoadMesh(std::string& Path, std::string& ResourceID)
	{
		if (Textures.find(ResourceID) == Textures.end())//Not found
		{
			Mesh* loadMesh = MeshLoader::ParseFile(Path);
			if (loadMesh)
			{
				Meshes[ResourceID] = loadMesh;
				return Meshes[ResourceID];
			}
			else 
			{
				return nullptr;
			}
		}
		else
		{
			return GetMesh(ResourceID);
		}
	}

	const Mesh* ResourceManager::GetMesh(std::string& ResourceID)
	{
		if (Meshes.find(ResourceID) == Meshes.end())//Not found
			return nullptr;
		return Meshes[ResourceID];
	}

	void ResourceManager::Clear()
	{
		for (auto iter : Shaders) {
			iter.second->Release();
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto iter : Textures) {
			iter.second->Release();
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto iter : Meshes) {
			iter.second->Release();
			delete iter.second;
			iter.second = nullptr;
		}

		Shaders.clear();
		Textures.clear();
		Meshes.clear();
	}

	std::string& ResourceManager::GetResourceDirectory() 
	{
		return ResourceDirectory;
	}


}