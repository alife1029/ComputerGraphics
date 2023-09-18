#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "App.h"
#include "utils/Input.h"
#include "utils/Window.hpp"

int main(int argc, char** argv)
{
	// Init GLFW library, because we will use it to create and mange window
	if (!glfwInit())
	{
		// If it fails, print out error and close the program
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	// Window creation
	Window* window = new Window();

	// Make the window we created the target rendering window
	window->SetAsTargetRenderingWindow();

	// Load Modern OpenGL features
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load Modern OpenGL!" << std::endl;

		// If it is failed, delete window, terminate GLFW and close the program
		delete window;
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

	// Create app insance
	App* app = new App();

	// V-Sync
	glfwSwapInterval(1);

	while (!window->ShouldClose())
	{
		// Update & Render app
		app->Update(static_cast<float>(deltaTime));
		app->Render();

		Input::Update();

		// Poll events and swap framebuffers
		glfwPollEvents();
		window->SwapBuffers();

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
				window->SetTitle(newTitle.c_str());

				lastTitleChange = int(timeStamp * 5);
			}

			if (Input::IsKeyJustPressed(Key::KEY_F11))
			{
				window->ToggleCursorVisibility();
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
