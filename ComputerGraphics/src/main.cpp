#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1024, 680, "Computer Graphics Playground", NULL, NULL);
	if (!window)
	{
		std::cout << "Falied to create GLFW window!" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
