#include "Input.h"

#include <GLFW/glfw3.h>

// Initialize vars
bool Input::keyStates[348] = { 0 };
bool Input::lastKeyStates[348] = { 0 };
glm::dvec2 Input::cursorPos = glm::vec2{ 0 };
glm::dvec2 Input::cursorDelta = glm::vec2{ 0 };

// Set listeners
void Input::SetListener(Window* window)
{
	glfwSetKeyCallback(window->m_WindowHandle, glfw_key_callback);						// Key callback
	glfwSetCursorPosCallback(window->m_WindowHandle, glfw_cursor_position_callback);	// Curor callback
}

void Input::Update()
{
	// Copy current keystates to the last key states
	for (size_t i = 0; i < std::size(keyStates); i++)
		lastKeyStates[i] = keyStates[i];

	cursorDelta = glm::dvec2(0.0f);
}

// This keyboard callback will be called by GLFW
void Input::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key != GLFW_KEY_UNKNOWN) // -1
	{
		keyStates[key] = static_cast<bool>(action);
	}
}

// This cursor callback will be called by GLFW
void Input::glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (cursorPos == glm::dvec2{ 0.0 })
	{
		cursorDelta = glm::dvec2{ 0.0 };
	}
	else
	{
		cursorDelta.x = xpos - cursorPos.x;
		cursorDelta.y = ypos - cursorPos.y;
	}
	cursorPos = { xpos, ypos };
}
