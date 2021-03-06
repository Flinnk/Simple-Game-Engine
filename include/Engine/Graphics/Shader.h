#pragma once 

#include <map>

namespace GameEngine {

	struct Vector3;
	struct Matrix4;

	class Shader
	{
	public:
		Shader();
		virtual ~Shader();

		Shader(Shader const&) = delete;
		Shader(Shader &&) = delete;
		Shader& operator= (Shader const&) = delete;
		Shader& operator= (Shader &&) = delete;

		void Use() const;
		bool Compile(const char* VertexShaderPath, const char* FragmentShaderPath);

		void SetVector3(const char* UniformName, Vector3 value) ;
		void SetMatrix4(const char* UniformName, Matrix4 value) ;
		void SetInteger(const char* UniformName, int value) ;

		void Release();

		unsigned int GetID()const;

	protected:
		unsigned int ID = 0;

	private:

		std::map<std::string, int> UniformLocationCache;
		int GetUniformLocation(const char* UniformName);
		bool CompileShader(int ShaderType, const char* ShaderSource, int &ShaderID);
		bool CheckCompilationErrors(int ShaderType, int Shader);
	};
}

