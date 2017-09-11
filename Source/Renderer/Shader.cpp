#include "Shader.h"
#include <GL\glew.h>

namespace GameEngine {


	Shader::Shader()
	{

	}

	Shader::~Shader()
	{
	}


	void Shader::Use() const
	{
		glUseProgram(ID);
	}

	bool Shader::Compile(const char* VertexShaderCode, const char* FragmentShaderCode)
	{
		int VertexShader, FragmentShader;
		if (!CompileShader(GL_VERTEX_SHADER, VertexShaderCode, VertexShader))
		{
			glDeleteShader(VertexShader);
			return false;
		}

		if (!CompileShader(GL_FRAGMENT_SHADER, FragmentShaderCode, FragmentShader))
		{
			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);
			return false;
		}

		ID = glCreateProgram();
		glAttachShader(ID, VertexShader);
		glAttachShader(ID, FragmentShader);

		glLinkProgram(ID);
		if (!CheckCompilationErrors(GL_PROGRAM, ID)) {
			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);
			return false;
		}

		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);

		return true;
	}

	bool Shader::CompileShader(int ShaderType, const char* ShaderSource, int &ShaderID)
	{
		int CreatedShader = glCreateShader(ShaderType);
		const GLchar* Source = ShaderSource;
		glShaderSource(CreatedShader, 1, &Source, 0);
		glCompileShader(CreatedShader);
		bool Result = CheckCompilationErrors(ShaderType, CreatedShader);
		ShaderID = Result ? CreatedShader : -1;
		return Result;
	}

	bool Shader::CheckCompilationErrors(int ShaderType, int Object)
	{
		int success;
		char log[1024];
		if (ShaderType != GL_PROGRAM)
		{
			glGetShaderiv(Object, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(Object, 1024, 0, log);
				//TODO: Log compilation error
			}
		}
		else
		{
			glGetProgramiv(Object, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(Object, 1024, 0, log);
				//TODO: Log compilation error
			}
		}

		return success != 0;
	}
}