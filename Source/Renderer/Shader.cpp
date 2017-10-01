#include "Shader.h"
#include <GL\glew.h>
#include "..\Math\Math.h"

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


	void Shader::SetVector3(const char* UniformName, Vector3 value) const
	{

		glUniform3f(glGetUniformLocation(ID, UniformName), value.x, value.y, value.z);
	}

	void Shader::SetInteger(const char* UniformName, int value) const
	{

		glUniform1i(glGetUniformLocation(ID, UniformName), value);
	}

	void Shader::SetMatrix4(const char* UniformName, Matrix4 value) const
	{

		glUniformMatrix4fv(glGetUniformLocation(ID, UniformName), 1, false, value.elements);
	}

	unsigned int Shader::GetID() const {
		return ID;
	}
}