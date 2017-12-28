#include <Engine\Utils\File.h>
#include <fstream>
#include <sstream>

namespace GameEngine
{

	std::string File::ReadFile(const std::string& Path)
	{
		std::string Content;
		std::ifstream File(Path);
		if (File) {
			std::stringstream Stream;
			Stream << File.rdbuf();
			File.close();
			Content = Stream.str();
		}

		return Content;
	}
}
