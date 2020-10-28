#pragma once
#include "Window.h"

class Graphics
{
private:
	struct Shaders {
		std::string VertexShader;
		std::string FragmentShader;
	};
public:
	Graphics();
	~Graphics();
	void init();
private:
	GLuint CompileShader(GLenum type, const std::string& ShaderSourceCode);
	GLuint CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	Shaders ShaderFileToString(const std::string& filepath);
private:
	const float vertices[8] = {
	-0.25f,  0.1f,  // 0
	-0.5f, -0.5f,   // 1
	 0.15f, -0.73f, // 2 
	 0.57f,  0.5f   // 3
	};
	GLuint indieces[6] = {
		0,1,2,
		2,3,0
	};
};

