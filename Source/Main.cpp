#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debug.h"
#include "Object.h"
#include "Shader.h"
#include "mat4x4.h"
#include "Camera.h"

#include <iostream>

//key calls
void KeyCall(GLFWwindow *window, int key, int scancode, int action, int mods);
void KeyPress(int key);
void KeyRelease(int key);
void KeyRepeat(int key);

//mousebutton calls
void MouseButtonCall(GLFWwindow* window, int button, int action, int mods);
void MouseButtonPress(int button);
void MouseButtonRelease(int button);

//cursor calls
void CursorCall(GLFWwindow *window, double xpos, double ypos);

//mousewheel calls
void MouseWheelCall(GLFWwindow* window, double xoffset, double yoffset);

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

	//key input
	glfwSetKeyCallback(window, KeyCall);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	//mousebutton input
	glfwSetMouseButtonCallback(window, MouseButtonCall);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	//cursor input
	glfwSetCursorPosCallback(window, CursorCall);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); //GLFW_CURSOR_NORMAL, GLFW_CURSOR_DISABLED, GLFW_CURSOR_HIDDEN
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	//mousewheel input
	glfwSetScrollCallback(window, MouseWheelCall);

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

		//basicShader->useShader();

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

void KeyCall(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
		case GLFW_PRESS:
			KeyPress(key);
			break;
		case GLFW_RELEASE:
			KeyRelease(key);
			break;
		case GLFW_REPEAT:
			KeyRepeat(key);
			break;
		default:
			break;
	}
}

void KeyPress(int key)
{
	std::cout << key << "key press event" << std::endl;

	if (key = GLFW_KEY_ESCAPE)
	{
		glfwTerminate();
		exit(0);
	}
}

void KeyRelease(int key)
{
	std::cout << key << "key release event" << std::endl;
}

void KeyRepeat(int key)
{
	std::cout << key << "key repeat event" << std::endl;
}

void MouseButtonCall(GLFWwindow * window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		MouseButtonPress(button);
		break;
	case GLFW_RELEASE:
		MouseButtonRelease(button);
		break;
	default:
		break;
	}
}

void MouseButtonPress(int button)
{
	std::cout << button << "mouse press event" << std::endl;
}

void MouseButtonRelease(int button)
{
	std::cout << button << "mouse release event" << std::endl;
}

void CursorCall(GLFWwindow * window, double xpos, double ypos)
{
	std::cout << "MouseXY-Coordinates:" << "[" << xpos << "|" << ypos << "]" << std::endl;
}

void MouseWheelCall(GLFWwindow * window, double xoffset, double yoffset)
{
	std::cout << yoffset << std::endl;	//vertical mousewheel provides value -1, (NoCall) and 1 on the y-axis
}
