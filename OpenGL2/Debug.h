#pragma once

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x)	if(!(x)) __debugbreak();
#define GL_CALL(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

static unsigned int WIDTH = 640;
static unsigned int HEIGHT = 480;

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char *function, const char *file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error] (" << error << ") " << function << std::endl << file << " : line " << line << std::endl;

		return false;
	}
	return true;
}