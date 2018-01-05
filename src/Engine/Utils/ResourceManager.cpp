

#include <Engine\Utils\ResourceManager.h>
#include <map>
#include <stb_image.h>
#include <Engine\Utils\File.h>
#include <Engine\Utils\MeshLoader.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace GameEngine
{

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	ResourceManager::ResourceManager()
	{
		std::string& ExecutionDirectory = File::GetExecutionDirectory();
		MountResourceDirectory(ExecutionDirectory.substr(0, ExecutionDirectory.find_last_of("\\")) + "\\Resources\\");
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

	Shader* ResourceManager::LoadShader(const char* ResourceRelativePath)
	{
		std::string ResourceID(ResourceRelativePath);
		if (Shaders.find(ResourceID) == Shaders.end())//Not found
		{
			Shader* shader = new Shader();
			ShaderSource source = ParseShader((ResourceDirectory + ResourceRelativePath).c_str());
			if (shader->Compile(source.VertexSource.c_str(), source.FragmentSource.c_str()))
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
			return GetShader(ResourceRelativePath);
		}
	}



	ShaderSource ResourceManager::ParseShader(const char* Path)
	{
		std::ifstream stream(Path);
		std::stringstream ss[2];
		ShaderType parsingShader;
		if (stream)
		{
			std::string line;
			while (getline(stream, line))
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
					{
						parsingShader = ShaderType::VERTEX;
					}
					else if (line.find("fragment") != std::string::npos)
					{
						parsingShader = ShaderType::FRAGMENT;
					}
				}
				else
				{
					ss[(int)parsingShader] << line << "\n";
				}
			}
		}

		return { ss[0].str(),ss[1].str() };
	}

	Shader* ResourceManager::GetShader(const char* ResourceRelativePath)
	{
		std::string ResourceID(ResourceRelativePath);
		if (Shaders.find(ResourceID) == Shaders.end())//Not found
			return nullptr;
		return Shaders[ResourceID];
	}


	const Texture* ResourceManager::LoadTexture(const char* ResourceRelativePath)
	{
		std::string ResourceID(ResourceRelativePath);
		if (Textures.find(ResourceID) == Textures.end())//Not found
		{
			Texture* LoadTexture = nullptr;

			int Width, Height, NrChannels;
			stbi_set_flip_vertically_on_load(false);
			unsigned char *Image = stbi_load((ResourceDirectory + ResourceRelativePath).c_str(), &Width, &Height, &NrChannels, 0);
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
			return GetTexture(ResourceRelativePath);
		}
	}

	const Texture* ResourceManager::GetTexture(const char* ResourceRelativePath)
	{
		std::string ResourceID(ResourceRelativePath);

		if (Textures.find(ResourceID) == Textures.end())//Not found
			return nullptr;
		return Textures[ResourceID];
	}

	const Mesh* ResourceManager::LoadMesh(const char* ResourceRelativePath)
	{
		std::string ResourceID(ResourceRelativePath);

		if (Meshes.find(ResourceID) == Meshes.end())//Not found
		{
			Mesh* loadMesh = MeshLoader::ParseFile(ResourceDirectory + ResourceRelativePath);
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
			return GetMesh(ResourceRelativePath);
		}
	}

	const Mesh* ResourceManager::GetMesh(const char* ResourceRelativePath)
	{
		std::string ResourceID(ResourceRelativePath);

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

	void ResourceManager::MountResourceDirectory(std::string RootDirectory)
	{
		ResourceDirectory = RootDirectory;
	}

}