#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Globals.h"
#include "Debug.h"
#include "Object.h"
#include "XYZ.h"
#include "Plane.h"
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

	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

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
	Shader *textureShader = new Shader("Resources/Shaders/Texture.shader");

	Object *object = new XYZ();
	object->initialize();
	Object *object2 = new Plane();
	object2->initialize();

	Camera camera;
	camera.initialize();
	camera.setPosition(vec3(0, -1, 0));

	object->translate(vec3(0, 0, 0));
	object2->translate(vec3(0, 0, 0));

	float delta = 0.f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		//basic shader 
		basicShader->useShader();

		basicShader->uniformMat4x4f("vmatrix", camera.getViewMatrix());
		basicShader->uniformMat4x4f("pmatrix", camera.getProjectionMatrix());
		basicShader->uniformMat4x4f("tmatrix", object->getTransformationMatrix());
		
		object->draw();

		//texture shader
		textureShader->useShader();

		textureShader->uniformMat4x4f("vmatrix", camera.getViewMatrix());
		textureShader->uniformMat4x4f("pmatrix", camera.getProjectionMatrix());
		textureShader->uniformMat4x4f("tmatrix", object2->getTransformationMatrix());

		object2->getTexture()->bind(object2->getTexture()->getTextureID());
		textureShader->uniformInt("textureSampler", object2->getTexture()->getTextureID());

		object2->draw();		

		//Camera movement
		camera.setPosition(camera.getPosition().lerp(vec3(0, 2, 2), vec3(3, 2, 2), delta));
		camera.setFocusPoint(camera.getFocusPoint().lerp(vec3(0, 0, 0), vec3(3, 0, 0), delta));

		camera.tick(0.f);

		//object->rotate(1.f, vec3(0, 1, 0));

		delta += 0.002f;
		if (delta >= 1.f)
			delta = 0.f;

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

void KeyPress(int key)	//GLFW_KEY_LAST = 348
{
	std::cout << key << "key press event" << std::endl;

	//Standard Controllers
	if (key == GLFW_KEY_ESCAPE)
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
	//std::cout << "MouseXY-Coordinates:" << "[" << xpos << "|" << ypos << "]" << std::endl;
}

void MouseWheelCall(GLFWwindow * window, double xoffset, double yoffset)
{
	std::cout << "mousewheel vertical offset:" << yoffset << std::endl;	//vertical mousewheel provides value -1, (NoCall) and 1 on the y-axis
}
