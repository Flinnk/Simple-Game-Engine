

#include "ResourceManager.h"
#include <GL\glew.h>
#include <map>
#include <stb_image.h>

namespace GameEngine
{
	ResourceManager::ResourceManager() {}
	ResourceManager::~ResourceManager() {}


	ResourceManager& ResourceManager::GetInstance()
	{
		static ResourceManager Instance;
		return Instance;
	}

	Shader* ResourceManager::LoadShader(std::string VertexSourceCode, std::string FragmentSourceCode, std::string ResourceID)//TODO: Use path instead of provided string as id?
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

	Shader* ResourceManager::GetShader(std::string ResourceID)
	{
		if (Shaders.find(ResourceID) == Shaders.end())//Not found
			return nullptr;
		return Shaders[ResourceID];
	}


	const Texture* ResourceManager::LoadTexture(std::string Path, std::string ResourceID)
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

	const Texture* ResourceManager::GetTexture(std::string ResourceID)
	{
		if (Textures.find(ResourceID) == Textures.end())//Not found
			return nullptr;
		return Textures[ResourceID];
	}

	void ResourceManager::Clear()
	{
		for (auto iter : Shaders) {
			glDeleteProgram(iter.second->GetID());
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto iter : Shaders) {
			const GLuint* ID = (GLuint*)iter.second->GetID();
			glDeleteTextures(1, ID);
			delete iter.second;
			iter.second = nullptr;
		}
	}

}