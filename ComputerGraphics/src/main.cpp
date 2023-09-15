#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "App.h"

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 8);

	GLFWwindow* window = glfwCreateWindow(1024, 680, "Computer Graphics Playground", NULL, NULL);
	if (!window)
	{
		std::cout << "Falied to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Load Modern OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load Modern OpenGL!" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	double timeStamp = glfwGetTime();
	double deltaTime = 0.0;

	App* app = new App();

	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		app->Update(deltaTime);

		glfwPollEvents();
		glfwSwapBuffers(window);

		deltaTime = glfwGetTime() - timeStamp;
		timeStamp = glfwGetTime();
	}

	delete app;

	glfwTerminate();
	return 0;
}
