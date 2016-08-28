#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "utils\OBJLoader.h"
#include "graphics\VertexArrayObject.h"
#include <iostream>

GLFWwindow* window;

static void errorCallback(int error, const char* description) {
	std::cerr << description << std::endl;
}

void init() {
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		exit(-1);

	//glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(1280, 720, "Planet", NULL, NULL);

	if (!window) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		exit(-2);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Set input callbacks
	//glfwSetKeyCallback(m_window, KeyInput::invoke);
	//glfwSetCursorPosCallback(m_window, MousePosInput::invoke);
	//glfwSetMouseButtonCallback(m_window, MouseButtonInput::invoke);

	// Check for errors
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		exit(-3);
	}

	glClearColor(0.2, 0.2, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Supported OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

int main() {
	init();

	OBJLoader loader;
	std::vector<glm::vec3> verts;
	std::vector<unsigned> indices;
	if (loader.loadFromFile("sphere.obj", verts, indices))
		std::cout << "Read file successfully!" << std::endl;
	else
		std::cout << "Did not read file" << std::endl;	

	VertexArrayObject sphere(verts, indices);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sphere.draw();

		glfwSwapBuffers(window);
	}

	return 0;
}