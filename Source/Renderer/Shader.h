#ifndef SHADER_H
#define SHADER_H
namespace GameEngine {

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

		void SetVector3(const char* UniformName, struct Vector3 value);
		void SetMatrix4(const char* UniformName, struct Matrix4 value);
		void SetInterger(const char* UniformName, int value);

		unsigned int GetID()const;

	protected:
		unsigned int ID = 0;

	private:

		bool CompileShader(int ShaderType, const char* ShaderSource, int &ShaderID);
		bool CheckCompilationErrors(int ShaderType, int Shader);
	};
}

#endif // !SHADER_H
