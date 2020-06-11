#pragma once

#include <iostream>
#include <unordered_map>

class mat4x4;
class vec3;
class vec2;

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
	std::unordered_map<std::string, int> mLocationCache;

public:
	Shader(const std::string &shaderPath);
	~Shader();

	int program() const { return mProgram; }
	void useShader();
	void deleteShader();

	ShaderProgramSource ParseShader(const std::string& filepath);
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	// utility uniform functions
	void uniformBool(const std::string &name, bool value);
	void uniformInt(const std::string &name, int value);
	void uniformf(const std::string &name, float value);
	void uniform2f(const std::string &name, float v1, float v2);
	void uniform2f(const std::string &name, const vec2 &values);
	void uniform3f(const std::string &name, float v1, float v2, float v3);
	void uniform3f(const std::string &name, const vec3 &values);
	void uniformMat4x4f(const std::string &name, mat4x4 mat);

private:
	int getUniformLocation(const std::string &name);
};

