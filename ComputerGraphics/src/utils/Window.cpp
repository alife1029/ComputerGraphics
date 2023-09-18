#include "Window.hpp"

#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(int width, int height, const std::string& title)
	:
	m_Width(width),
	m_Height(height)
{
	// Antialiasing
	glfwWindowHint(GLFW_SAMPLES, 8);

	m_WindowHandle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!m_WindowHandle)
	{
		std::cout << "Falied to create GLFW window!" << std::endl;
		throw "Failed to create GLFW window!";
	}

	m_Title = title;
}

Window::~Window()
{
	glfwDestroyWindow(m_WindowHandle);
}

void Window::SetTitle(const std::string& title)
{
	glfwSetWindowTitle(m_WindowHandle, title.c_str());
	m_Title = title;
}

void Window::SetCursorVisibility(bool visible)
{
	glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	m_CursorVisible = visible;
}

void Window::ToggleCursorVisibility()
{
	SetCursorVisibility(!m_CursorVisible);
}

void Window::SetAsTargetRenderingWindow()
{
	glfwMakeContextCurrent(m_WindowHandle);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_WindowHandle) != 0;
}

void Window::SwapBuffers() const
{
	glfwSwapBuffers(m_WindowHandle);
}
