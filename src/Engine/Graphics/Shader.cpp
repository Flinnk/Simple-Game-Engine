#include <Engine\Graphics\Shader.h>
#include <Engine\Graphics\OpenGL.h>
#include <Engine\Math\Math.h>
#include <Engine\Utils\Log.h>

namespace GameEngine {


	Shader::Shader()
	{

	}

	Shader::~Shader()
	{
	}


	void Shader::Use() const
	{
		GLCall(glUseProgram(ID));
	}

	bool Shader::Compile(const char* VertexShaderCode, const char* FragmentShaderCode)
	{
		int VertexShader, FragmentShader;
		if (!CompileShader(GL_VERTEX_SHADER, VertexShaderCode, VertexShader))
		{
			GLCall(glDeleteShader(VertexShader));
			return false;
		}

		if (!CompileShader(GL_FRAGMENT_SHADER, FragmentShaderCode, FragmentShader))
		{
			GLCall(glDeleteShader(VertexShader));
			GLCall(glDeleteShader(FragmentShader));
			return false;
		}

		ID = GLCall(glCreateProgram());
		GLCall(glAttachShader(ID, VertexShader));
		GLCall(glAttachShader(ID, FragmentShader));

		GLCall(glLinkProgram(ID));
		if (!CheckCompilationErrors(GL_PROGRAM, ID)) {
			GLCall(glDeleteShader(VertexShader));
			GLCall(glDeleteShader(FragmentShader));
			return false;
		}

		GLCall(glDeleteShader(VertexShader));
		GLCall(glDeleteShader(FragmentShader));

		return true;
	}

	bool Shader::CompileShader(int ShaderType, const char* ShaderSource, int &ShaderID)
	{
		int CreatedShader = GLCall(glCreateShader(ShaderType));
		const GLchar* Source = ShaderSource;
		GLCall(glShaderSource(CreatedShader, 1, &Source, 0));
		GLCall(glCompileShader(CreatedShader));
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
			GLCall(glGetShaderiv(Object, GL_COMPILE_STATUS, &success));
			if (!success)
			{
				GLCall(glGetShaderInfoLog(Object, 1024, 0, log));
				Log(log);
			}
		}
		else
		{
			GLCall(glGetProgramiv(Object, GL_LINK_STATUS, &success));
			if (!success)
			{
				GLCall(glGetProgramInfoLog(Object, 1024, 0, log));
				Log(log);
			}
		}

		return success != 0;
	}


	void Shader::SetVector3(const char* UniformName, Vector3 value) 
	{

		GLCall(glUniform3f(GetUniformLocation(UniformName), value.x, value.y, value.z));
	}

	void Shader::SetInteger(const char* UniformName, int value) 
	{

		GLCall(glUniform1i(GetUniformLocation(UniformName), value));
	}

	void Shader::SetMatrix4(const char* UniformName, Matrix4 value) 
	{

		GLCall(glUniformMatrix4fv(GetUniformLocation(UniformName), 1, false, value.elements));
	}

	int Shader::GetUniformLocation(const char* UniformName)
	{
		std::string name = UniformName;
		if (UniformLocationCache.find(name) != UniformLocationCache.end())
			return UniformLocationCache[name];

		int location = GLCall(glGetUniformLocation(ID, UniformName));
		if (location == -1)
			LogFormat("Shader ID: %d failed to retrive uniform with name %s",ID,UniformName);

			UniformLocationCache[name] = location;
		return location;
	}

	unsigned int Shader::GetID() const {
		return ID;
	}

	void Shader::Release()
	{
		GLCall(glDeleteProgram(ID));
		ID = 0;
	}
}