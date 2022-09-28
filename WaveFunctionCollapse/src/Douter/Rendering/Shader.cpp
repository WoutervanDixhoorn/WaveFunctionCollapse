#include "Shader.h"

#include <iostream>
#include <fstream>

#include <glad/glad.h>

#include <glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Douter {

	Shader::Shader(const char* filePath)
	{
		ShaderSource source = loadShaderFile(filePath);

		unsigned int vs = compileShader(source.vertexShader.c_str(), GL_VERTEX_SHADER);
		unsigned int fs = compileShader(source.fragmentShader.c_str(), GL_FRAGMENT_SHADER);

		m_Id = glCreateProgram();

		glAttachShader(m_Id, vs);
		glAttachShader(m_Id, fs);
		glLinkProgram(m_Id);

		glUseProgram(m_Id);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	Shader::~Shader()
	{
	}

	ShaderSource Shader::loadShaderFile(const char* filePath)
	{
		std::string source[2] = { "", "" };

		std::ifstream fs(filePath);

		int state = 0;//State 0 = vertex, State 1 = fragment
		std::string line;
		if (fs.is_open())
		{
			while (getline(fs, line))
			{
				if (line.find("#vertexShader") != std::string::npos) {
					state = 0;
				}
				else if (line.find("#fragmentShader") != std::string::npos) {
					state = 1;
				}
				else {
					source[state] += line + '\n';
				}
			}
		}
		else {
			std::cout << "ERROR: Shader path given not found: " << filePath << "\n";
		}
		fs.close();

		return { source[0], source[1] };
	}

	unsigned int Shader::compileShader(const char* source, int shaderType)
	{
		unsigned int shader;
		shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		int  success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::"<< ((shaderType == GL_FRAGMENT_SHADER) ? "FRAGMENT" : "VERTEX") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		return shader;
	}

	void Shader::Bind() const
	{
		glUseProgram(m_Id);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	template <>
	void Shader::SetUniform(const char* name, const int& data)
	{
		unsigned int uLocation = glGetUniformLocation(m_Id, name);
		glUniform1i(uLocation, data);
	}

	template <>
	void Shader::SetUniform(const char* name, const float& data)
	{
		unsigned int uLocation = glGetUniformLocation(m_Id, name);
		glUniform1f(uLocation, data);
	}

	template <>
	void Shader::SetUniform(const char* name, const glm::vec2& data)
	{
		unsigned int uLocation = glGetUniformLocation(m_Id, name);
		glUniform2fv(uLocation, 1, glm::value_ptr(data));
	}

	template <>
	void Shader::SetUniform(const char* name, const glm::vec3& data)
	{
		unsigned int uLocation = glGetUniformLocation(m_Id, name);
		glUniform3fv(uLocation, 1, &data[0]);
	}

	template <>
	void Shader::SetUniform(const char* name, const glm::vec4& data)
	{
		unsigned int uLocation = glGetUniformLocation(m_Id, name);
		glUniform4fv(uLocation, 1, glm::value_ptr(data));
	}

	template <>
	void Shader::SetUniform(const char* name, const glm::mat4& data)
	{
		unsigned int uLocation = glGetUniformLocation(m_Id, name);
		glUniformMatrix4fv(uLocation, 1, GL_FALSE, &data[0][0]);
	}

}