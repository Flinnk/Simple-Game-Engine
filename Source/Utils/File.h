#ifndef FILE_H
#define FILE_H

#include <string>


namespace GameEngine {
	class File {

	public:

		static std::string ReadFile(std::string Path);//Support only Absolute path
		static std::string GetExecutionDirectory();
	};
}

#endif // !FILE_H