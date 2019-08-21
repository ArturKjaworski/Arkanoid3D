#include "pch.h"
#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileName)
{
	program = glCreateProgram();

	shaders[EShaderType::VERTEX] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	shaders[EShaderType::FRAGMENT] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for (size_t ii = 0; ii < EShaderType::COUNT; ++ii)
		glAttachShader(program, shaders[ii]);

	glBindAttribLocation(program, 0, "position");			//what part of data read in shader
	glBindAttribLocation(program, 1, "vertexUV");

	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Program linking error");

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Program is invalid");
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cout << "Shader creation error" << std::endl;
		return 0;
	}

	const char* shaderSourceStrings = text.c_str();
	int shaderSourceStrLen = text.length();

	glShaderSource(shader, 1, &shaderSourceStrings, &shaderSourceStrLen);

	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "shader comp error");

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string out;
	std::string line;

	if (!file.is_open())
	{
		std::cout << std::endl << "Unable to load shader file " << fileName << std::endl;
		return "";
	}

	while (file.good())
	{
		getline(file, line);
		out.append(line + "\n");
	}
	return out;
}

Shader::~Shader()
{
	
	for (size_t ii = 0; ii < EShaderType::COUNT; ++ii)
	{
		glDetachShader(program, shaders[ii]);
		glDeleteShader(shaders[ii]);
	}

	glDeleteProgram(program);
}

void Shader::Bind() const
{
	glUseProgram(program);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string & name, int val)
{
	glUniform1i(GetUniformLocation(name), val);
}

void Shader::SetUniform4f(const std::string& location, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(location), x, y, z, w);
}

void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 & mat)
{
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, false, &mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name) const
{
	int location = glGetUniformLocation(program, name.c_str());
	if (location == -1)
		std::cout << "location doesnt exist: " << name << std::endl;
	
	return location;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cout << std::endl << errorMsg << ": " << error << std::endl;
	}
}
