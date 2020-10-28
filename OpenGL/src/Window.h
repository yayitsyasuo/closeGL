#pragma once
#define GLFW_INCLUDE_NONE
#include <glew.h>
#include <glfw3.h>
#include <string>

class Window
{
public:
	Window( int width, int height, const char* WindowName );
	Window( const Window& win ) = delete;
	Window& operator=( const Window& win ) = delete;
	~Window();
	int Go();
private:
	GLFWwindow* handle = nullptr;
};

