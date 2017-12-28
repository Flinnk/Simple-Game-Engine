#include <Engine\Utils\MeshLoader.h>
#include <Engine\Graphics\Mesh.h>
#include <Engine\Math\Math.h>
#include <sstream>
#include <fstream>
#include <Engine\Utils\Log.h>
#include <vector>
namespace GameEngine
{
	Mesh* MeshLoader::ParseFile(const std::string& Path)
	{
		Mesh* loadedMesh = nullptr;
		if (Path.find(".obj") >= 0)
		{
			std::vector<Vector3> vertices;
			std::vector<Vector3> normals;
			std::vector<unsigned int> indices;

			std::string line;
			std::ifstream stream(Path);
			if (stream)
			{
				while (std::getline(stream, line))
				{
					std::istringstream stringStream(line);
					std::string character;
					stringStream >> character;
					if (character == "v")
					{
						Vector3 vertex;
						for (int i = 0; i < 3; ++i)
						{
							stringStream >> vertex.elements[i];
						}
						vertices.push_back(vertex);
					}
					else if (character == "vn")
					{
						Vector3 vertex;
						for (int i = 0; i < 3; ++i)
						{
							stringStream >> vertex.elements[i];
						}
						normals.push_back(vertex);
					}
					else if (character == "f")
					{
						unsigned int index = 0;
						while (stringStream >> index)
							indices.push_back(index);
					}


				}

				if (indices.size() > 0 && vertices.size() > 0)
				{
					float* data = new float[indices.size() * 3];
					float* dataPointer = data;
					int i = 0;
					LogFormat("Size: %d\n", indices.size() * 3);
					while (i < indices.size())
					{
						unsigned int index = indices[i] - 1;
						Vector3& vertex = vertices[index];

						*dataPointer = vertex.x;
						LogFormat("x: %f\n", *dataPointer);

						++dataPointer;

						*dataPointer = vertex.y;
						LogFormat("y: %f\n", *dataPointer);

						++dataPointer;

						*dataPointer = vertex.z;
						LogFormat("z: %f\n", *dataPointer);

						++dataPointer;

						++i;
						Log("\n");

					}

					dataPointer = nullptr;

					loadedMesh = new Mesh(data, sizeof(float)*3*indices.size());
					delete data;
				}

				stream.close();
			}
		}

		return loadedMesh;
	}

}