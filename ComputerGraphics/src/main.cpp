#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "App.h"
#include "utils/Input.h"

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

	Input::SetListener(window);

	// Enable required OpenGL features
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	double timeStamp = glfwGetTime();
	double deltaTime = 0.0;

	int lastTitleChange = 0;
	bool cursorHidden = false;

	// Create app insance
	App* app = new App();

	// V-Sync
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))
	{
		// Update & Render app
		app->Update(static_cast<float>(deltaTime));
		app->Render();

		Input::Update();

		// Poll events and swap framebuffers
		glfwPollEvents();
		glfwSwapBuffers(window);

		// Update time
		deltaTime = glfwGetTime() - timeStamp;
		timeStamp = glfwGetTime();

		{
			// Update Window Title
			if (int(timeStamp * 5) != lastTitleChange)
			{
				std::ostringstream oss;
				oss << "Computer Graphics Playground (" << int(1 / deltaTime) << " FPS)";
				std::string newTitle = oss.str();
				glfwSetWindowTitle(window, newTitle.c_str());

				lastTitleChange = int(timeStamp * 5);
			}

			if (Input::IsKeyPress(Key::KEY_F11))
			{
				cursorHidden = !cursorHidden;
				glfwSetInputMode(window, GLFW_CURSOR, cursorHidden ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			}
		}
	}

	// Delete app instance
	delete app;

	// Terminate GLFW library
	glfwTerminate();

	// End program
	return 0;
}
