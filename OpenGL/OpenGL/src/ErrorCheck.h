#pragma once
#include <glfw3.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>


std::ifstream& GotoLine(std::ifstream& file, unsigned int num) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

inline bool PrintError(GLenum err, const int line, const char* file) {

	if (!err)
		return true;
	
	// this function could create sheisse
	std::ostringstream err_hex;
	err_hex << "0x0" << std::hex << err;

	std::ifstream in("C:/Users/Martin/source/repos/OpenGL/Dependencies/GLEW/include/GL/glew.h");
	if (!in.good()) {
		return -1;
	}

	GotoLine(in, 313);
	std::string s;
	while (true) {
		getline(in, s);
		if (s.find(err_hex.str()) != std::string::npos) {	
			break;
		}
	}


	std::cout << "Error encoutered!" << std::endl;
	std::cout << "[FILE]: " << file << std::endl;
	std::cout << "[LINE]: " << line << std::endl;
	std::cout << "[Message]: " << s << std::endl;

	return false;
}
	
	




// my custom assert because __debugbreak() is great
#define ASSERT(x)	if(!(x)) __debugbreak();
#define ErrCheck(err) ASSERT(PrintError(err, __LINE__, __FILE__ ));