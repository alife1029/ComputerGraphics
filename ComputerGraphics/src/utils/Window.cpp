#include "Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

static std::map<GLFWwindow*, Window*> s_Windows = { };

Window::Window(int width, int height, const std::string& title, bool fullScreen)
	:
	m_Width(width),
	m_Height(height),
	m_FullScreen(fullScreen)
{
	// Antialiasing
	glfwWindowHint(GLFW_SAMPLES, 8);

	m_WindowHandle = glfwCreateWindow(width, height, title.c_str(), fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (!m_WindowHandle)
	{
		std::cout << "Falied to create GLFW window!" << std::endl;
		throw "Failed to create GLFW window!";
	}

	glfwSetFramebufferSizeCallback(m_WindowHandle, framebuffer_size_callback);

	m_Title = title;
	s_Windows.insert({ m_WindowHandle, this });
}

Window::~Window()
{
	s_Windows.erase(m_WindowHandle);
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

void Window::GoFullScreen()
{
	GLFWmonitor* montior = glfwGetPrimaryMonitor();
	const GLFWvidmode* vidMode = glfwGetVideoMode(montior);

	m_Width = vidMode->width;
	m_Height = vidMode->height;

	glfwSetWindowMonitor(m_WindowHandle, montior, 0, 0, m_Width, m_Height, vidMode->refreshRate);
	m_FullScreen = true;
}

void Window::GoWindowed()
{
	glfwSetWindowMonitor(m_WindowHandle, NULL, 60, 90, m_Width, m_Height, GLFW_DONT_CARE);
	m_FullScreen = false;
}

void Window::ToggleFullscreen()
{
	m_FullScreen ? GoWindowed() : GoFullScreen();
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

// Framebuffer resized callback
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Window* wnd = s_Windows[window];
	wnd->m_Width = width;
	wnd->m_Height = height;
	glViewport(0, 0, width, height);
}
