#pragma once 

//TODO: Add different output displays: File, InEngine...

namespace GameEngine
{
	/**
	* Sends a text to display in the debug output
	* @param Text to log
	*/
	void Log(const char* Text);

	/**
	* Sends a text with a variable list of parameters to display in the debug output
	* Example LogFormat("Some text with token %d", 123);
	* @param Text to log
	*/
	void LogFormat(const char* Text, ...);
}

