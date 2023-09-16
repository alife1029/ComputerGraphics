#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "App.h"

int main(int argc, char** argv)
{
	// Init GLFW library, because we will use it to create and mange window
	if (!glfwInit())
	{
		// If it fails, print out error and close the program
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	// Antialiasing
	glfwWindowHint(GLFW_SAMPLES, 8);

	// Window creation
	GLFWwindow* window = glfwCreateWindow(1024, 680, "Computer Graphics Playground", NULL, NULL);
	if (!window)
	{
		// If window did not created, terminate GLFW then close the program
		std::cout << "Falied to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window we created the target rendering window
	glfwMakeContextCurrent(window);

	// Load Modern OpenGL features
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load Modern OpenGL!" << std::endl;

		// If it is failed, delete window, terminate GLFW and close the program
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// Enable required OpenGL features
	glEnable(GL_DEPTH_TEST);

	double timeStamp = glfwGetTime();
	double deltaTime = 0.0;

	// Create app insance
	App* app = new App();

	// V-Sync
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		// Update app
		app->Update(deltaTime);

		// Poll events and swap framebuffers
		glfwPollEvents();
		glfwSwapBuffers(window);

		// Update time
		deltaTime = glfwGetTime() - timeStamp;
		timeStamp = glfwGetTime();
	}

	// Delete app instance
	delete app;

	// Terminate GLFW library
	glfwTerminate();

	// End program
	return 0;
}
