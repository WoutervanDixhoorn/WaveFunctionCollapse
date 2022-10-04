#pragma once
#include <string>

namespace Douter {

	struct ShaderSource
	{
		std::string vertexShader;
		std::string fragmentShader;
	};

	class Shader
	{
	private:
		unsigned int m_Id;

	private:
		ShaderSource loadShaderFile(const char* filePath);
		unsigned int compileShader(const char* source, int shaderType);

	public:
		Shader(const char* filePath);
		~Shader();

		inline unsigned int GetID() { return m_Id; }

		void Bind() const;
		void Unbind() const;

		template <typename T>
		void SetUniformArray(const char* name, const int count, const T* data);

		template <typename T>
		void SetUniform(const char* name, const T& data);
	};

}