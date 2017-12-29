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
			std::vector<Vector3> textCoords;

			std::vector<unsigned int> vertexIndices, normalIndices, textCoordIndices;

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
					else if (character == "vt")
					{
						Vector3 vertex;
						for (int i = 0; i < 3; ++i)
						{
							stringStream >> vertex.elements[i];
						}
						textCoords.push_back(vertex);
					}
					else if (character == "f")
					{
						std::string indices;

						unsigned int vertexIndex, uvIndex, normalIndex;

						while (stringStream >> indices)
						{
							int matches = sscanf(indices.c_str(), "%d/%d/%d", &vertexIndex, &uvIndex, &normalIndex);
							if (matches != 3) {
								return false;
							}

							vertexIndices.push_back(vertexIndex);
							textCoordIndices.push_back(uvIndex);
							normalIndices.push_back(normalIndex);
						}

						
					}


				}

				if ((vertexIndices.size() == normalIndices.size() && vertexIndices.size() == textCoordIndices.size()) && (vertexIndices.size() > 0 && vertices.size() > 0) && (normalIndices.size() > 0 && normals.size() > 0) && (textCoordIndices.size() > 0 && textCoords.size() > 0))
				{
					float* data = new float[vertexIndices.size() * 8];
					float* dataPointer = data;
					int i = 0;
					while (i < vertexIndices.size())
					{
						unsigned int vertexIndex = vertexIndices[i] - 1;
						unsigned int normalIndex = normalIndices[i] - 1;
						unsigned int textCordIndex = textCoordIndices[i] - 1;

						Vector3& vertex = vertices[vertexIndex];
						Vector3& normal = normals[normalIndex];
						Vector3& textCoord = textCoords[textCordIndex];

						*dataPointer = vertex.x;

						++dataPointer;

						*dataPointer = vertex.y;

						++dataPointer;

						*dataPointer = vertex.z;

						++dataPointer;

						*dataPointer = normal.x;

						++dataPointer;

						*dataPointer = normal.y;

						++dataPointer;

						*dataPointer = normal.z;

						++dataPointer;

						*dataPointer = textCoord.x;

						++dataPointer;

						// NOTE: Texture coordinates are Y flipped upside-down.Invert the V texture coordinates to left hand system.

						*dataPointer = 1.0f-textCoord.y;

						++dataPointer;

						++i;

					}

					dataPointer = nullptr;

					loadedMesh = new Mesh(data, sizeof(float) * 8 * vertexIndices.size());
					delete data;
				}

				stream.close();
			}
		}

		return loadedMesh;
	}

}