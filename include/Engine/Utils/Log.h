#ifndef LOG_H
#define LOG_H

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
	* @param Text to log
	*/
	void LogFormat(const char* Text, ...);
}

#endif // !LOG_H
