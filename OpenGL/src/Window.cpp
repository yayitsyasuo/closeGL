#include "Window.h"
#include <iostream>
#include "ErrorCheck.h"

#define PRINT_ERROR() std::cout << glfwGetError(NULL)

Window::Window(int width, int height, const char* WindowName)
{
	/* Initialize the library */
	if (!glfwInit())
		PRINT_ERROR();

		/* Create a windowed mode window and its OpenGL context */
	handle = glfwCreateWindow(width, height, WindowName, NULL, NULL);

	if (!handle)
		PRINT_ERROR();

	/* Make the window's context current */
	glfwMakeContextCurrent(handle);

	if (glewInit() != GLEW_OK)
		PRINT_ERROR();
}

Window::~Window()
{
	glfwTerminate();
}

int Window::Go()
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(handle))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_INT, NULL);
		ErrCheck(glGetError());

		/* Swap front and back buffers */
		glfwSwapBuffers(handle);

		/* Poll for and process events */
		glfwPollEvents();
	}

	return 0;
}
