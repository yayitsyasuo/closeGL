#include "Graphics.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

Graphics::Graphics() // setting up the buffers based on private memebers
{
	//vertex buffer
	GLuint uint;
	glGenBuffers(1, &uint);
	glBindBuffer(GL_ARRAY_BUFFER, uint);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	//index buffer 
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indieces), indieces, GL_DYNAMIC_DRAW);
}

void Graphics::init()
{
	Shaders shaders = ShaderFileToString("res/Shader/Shaders.shader");
	GLuint ShaderProgramID = CreateShader(shaders.VertexShader, shaders.FragmentShader);
	glUseProgram(ShaderProgramID);
	glDeleteProgram(ShaderProgramID);

}

Graphics::~Graphics()
{
}

GLuint Graphics::CompileShader(GLenum type, const std::string& ShaderSourceCode) {
	GLuint sID = glCreateShader(type);
	const GLchar* pSrc = ShaderSourceCode.c_str();
	glShaderSource(sID, 1, &pSrc, NULL);
	glCompileShader(sID);

	// error handling
	GLint error;
	glGetShaderiv(sID, GL_COMPILE_STATUS, &error);
	if (error == GL_FALSE) {
		GLint error_length;
		glGetShaderiv(sID, GL_INFO_LOG_LENGTH, &error_length);
		GLchar* err_msg = new GLchar[error_length];
		GLint error_result_length;
		glGetShaderInfoLog(sID, error_length, &error_result_length, err_msg);

		std::cout << "Failed to compile the shader, following error:" << std::endl;
		std::cout << err_msg;
		glDeleteShader(sID);
		delete[] err_msg;
		return 0;
	}
	return sID;
}

GLuint Graphics::CreateShader(const std::string& VertexShader, const std::string& FragmentShader) {
	// a program to which shaders will be attached, compiled and linked
	GLuint programID = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	glAttachShader(programID, vs);
	glAttachShader(programID, fs);
	glLinkProgram(programID);
	// for error purposes
	glValidateProgram(programID);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return programID;
}

Graphics::Shaders Graphics::ShaderFileToString(const std::string& filepath) {
	std::ostringstream oss[2];

	enum class Type {
		VertexShader = 0,
		FragmentShader = 1,
	};
	Type type;

	std::ifstream iFile(filepath);

	std::string line;
	while (getline(iFile, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("Vertex") != std::string::npos) {
				type = Type::VertexShader;
			}
			else if (line.find("Fragment") != std::string::npos) {
				type = Type::FragmentShader;
			}
		}
		else {
			oss[(int)type] << line << std::endl;
		}
	}

	return { oss[0].str(),  oss[1].str() };
}

