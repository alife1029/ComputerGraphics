#pragma once

#include <string>

struct GLFWwindow;

class Window
{
	friend class Input;
public:
	Window(int width = 1024, int height = 640, const std::string& title = "Computer Graphics Playground");
	~Window();

	void SetAsTargetRenderingWindow();
	bool ShouldClose() const;
	void SwapBuffers() const;

	void SetTitle(const std::string& title);
	void SetCursorVisibility(bool visible);
	void ToggleCursorVisibility();

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	std::string GetTitle() const { return m_Title; }
	bool IsCursorVisible() const { return m_CursorVisible; }
private:
	std::string		m_Title;
	int				m_Width;
	int				m_Height;
	bool			m_CursorVisible = true;
	GLFWwindow*		m_WindowHandle;
};
