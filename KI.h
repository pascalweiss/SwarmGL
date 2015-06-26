#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
class KI
{
private:
	GLuint programID;
	GLFWwindow* window;
	void init();
	void initGLFW();
	void initGLEW();
	static void KI::error_callback(int error, const char* description) {
		fputs(description, stderr);
	}
	void start();
public:
	KI(void);
	~KI(void);
};

