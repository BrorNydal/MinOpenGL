#pragma once

#include <iostream>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

//No classes derived from this, therefore no protected variables or functions
class Shader
{
private://variables
	int mProgram;
	ShaderProgramSource *mShaderProgramSource = nullptr;

public:
	Shader(std::string shaderPath);
	~Shader();

	int program() const { return mProgram; }
	void useShader();
	void deleteShader();

	ShaderProgramSource ParseShader(const std::string& filepath);
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	// utility uniform functions
	/*void uniformBool(const std::string &name, bool value);
	void uniformInt(const std::string &name, int value);
	void uniformf(const std::string &name, float value);
	void uniform2f(const std::string &name, float v1, float v2);
	void uniform2f(const std::string &name, const Vector2D &values);
	void uniform3f(const std::string &name, float v1, float v2, float v3);
	void uniform3f(const std::string &name, const Vector3D &values);
	void uniformMat4x4f(const std::string &name, QMatrix4x4 mat);*/
};

