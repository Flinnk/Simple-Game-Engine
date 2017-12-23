#pragma once 

#include <string>


namespace GameEngine {

	/*
	* Class to handle File information or content
	*/
	class File {

	public:

		/**
		* Reads the context of a text file
		* @param Path Absolute path to the file
		* @return Content of the file
		*/
		static std::string ReadFile(std::string Path);//Support only Absolute path

		/**
		* Returns the executable's absolute path
		* @return Abolute path to the current executable
		*/
		static std::string GetExecutionDirectory();
	};
}

