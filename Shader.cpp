#include "Shader.h"

//GL library
#include <GL/glew.h>

//My files
#include "Debug.h"

//std library
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(std::string shaderPath)
{
	ShaderProgramSource sps = ParseShader(shaderPath);
	mProgram = CreateShader(sps.VertexSource, sps.FragmentSource);
}

Shader::~Shader()
{
}

void Shader::useShader()
{
	GL_CALL(glUseProgram(mProgram));
}

void Shader::deleteShader()
{
	GL_CALL(glDeleteProgram(mProgram));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::fstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GL_CALL(glAttachShader(program, vs));
	GL_CALL(glAttachShader(program, fs));
	GL_CALL(glLinkProgram(program));
	GL_CALL(glValidateProgram(program));

	GL_CALL(glDeleteShader(vs));
	GL_CALL(glDeleteShader(fs));

	return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//ERROR HANDLING
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char *message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;

		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

//void Shader::uniformBool(const std::string &name, bool value)
//{
//	int loc = glGetUniformLocation(ID, name.c_str());
//
//	if (loc != -1)
//		glUniform1i(loc, static_cast<int>(value));
//	else
//		std::cout << "Uniform " << name.c_str() << " doesent exist." << std::endl;
//}
//
//void Shader::uniformInt(const std::string &name, int value)
//{
//	int loc = glGetUniformLocation(ID, name.c_str());
//
//	if (loc != -1)
//		glUniform1i(loc, value);
//	else
//		std::cout << "Uniform " << name.c_str() << " doesent exist." << std::endl;
//}
//
//void Shader::uniformf(const std::string &name, float value)
//{
//	int loc = glGetUniformLocation(ID, name.c_str());
//
//	if (loc != -1)
//		glUniform1f(loc, value);
//	else
//		std::cout << "Uniform " << name.c_str() << " doesent exist." << std::endl;
//}
//
//void Shader::uniform2f(const std::string &name, float v1, float v2)
//{
//	int loc = glGetUniformLocation(ID, name.c_str());
//
//	if (loc != -1)
//		glUniform2f(loc, v1, v2);
//	else
//		std::cout << "Uniform " << name.c_str() << " doesent exist." << std::endl;
//}
//
//void Shader::uniform2f(const std::string &name, const Vector2D &values)
//{
//	uniform2f(name, values.x(), values.y());
//}
//
//void Shader::uniform3f(const std::string &name, float v1, float v2, float v3)
//{
//	int loc = glGetUniformLocation(ID, name.c_str());
//
//	if (loc != -1)
//		glUniform3f(loc, v1, v2, v3);
//	else
//		std::cout << "Uniform " << name.c_str() << " doesent exist." << std::endl;
//}
//
//void Shader::uniform3f(const std::string &name, const Vector3D &values)
//{
//	uniform3f(name, values.x(), values.y(), values.z());
//}
//
//void Shader::uniformMat4x4f(const std::string &name, QMatrix4x4 mat)
//{
//	int loc = glGetUniformLocation(ID, name.c_str());
//
//	if (loc != -1)
//		glUniformMatrix4fv(loc, 1, GL_FALSE, mat.data());
//	else
//		std::cout << "Uniform " << name.c_str() << " doesent exist." << std::endl;
//}