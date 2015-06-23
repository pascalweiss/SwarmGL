#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
class KI
{
private:
	GLuint programID;
	GLFWwindow* window;
	int initialize();
	void error_callback(int error, const char* description);
	void start();
public:
	KI(void);
	~KI(void);
};

