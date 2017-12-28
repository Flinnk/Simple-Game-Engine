#pragma once 
#include <string>

namespace GameEngine
{
	class Mesh;
	class MeshLoader
	{
	public:
		static Mesh* ParseFile(const std::string& Path);

	};
}