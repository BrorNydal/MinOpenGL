#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debug.h"
#include "Object.h"
#include "Shader.h"
#include "mat4x4.h"
#include "Camera.h"

#include <iostream>

void KeyboardPress(unsigned char key);

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int WIDTH = 600, HEIGHT = 500;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	Shader *basicShader = new Shader("Resources/Shaders/Basic.shader");
	basicShader->useShader();	

	Object *object = new Object();
	object->initialize();

	Camera camera;
	camera.initialize();
	camera.setPosition(vec3(1, 1, 1));
	camera.setFocusPoint(vec3(0, 0, 0));
	 
	std::cout << camera.getViewMatrix() << std::endl;
	camera.tick(0.f);
	std::cout << camera.getViewMatrix() << std::endl;
	
	GL_CALL(glUniformMatrix4fv(glGetUniformLocation(basicShader->program(), "vmatrix"), 1, GL_TRUE, camera.getViewMatrix().data()				));
	GL_CALL(glUniformMatrix4fv(glGetUniformLocation(basicShader->program(), "pmatrix"), 1, GL_TRUE, camera.getProjectionMatrix().data()			));
	GL_CALL(glUniformMatrix4fv(glGetUniformLocation(basicShader->program(), "tmatrix"), 1, GL_TRUE, object->getTransformationMatrix().data()	));

	object->translate(vec3(0.f, 0.f, 0.f));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		basicShader->useShader();

		GL_CALL(glUniformMatrix4fv(glGetUniformLocation(basicShader->program(), "vmatrix"), 1, GL_TRUE, camera.getViewMatrix().data()				));
		GL_CALL(glUniformMatrix4fv(glGetUniformLocation(basicShader->program(), "pmatrix"), 1, GL_TRUE, camera.getProjectionMatrix().data()			));
		GL_CALL(glUniformMatrix4fv(glGetUniformLocation(basicShader->program(), "tmatrix"), 1, GL_TRUE, object->getTransformationMatrix().data()	));

		
		object->draw();

		object->rotate(1.f, vec3(0, 1, 0));

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	basicShader->deleteShader();

	glfwTerminate();
	return 0;
}

void KeyboardPress(unsigned char key)
{
	if (key == 27)
		exit(0);
}
