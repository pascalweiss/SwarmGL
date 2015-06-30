#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
class KI
{
private:
	GLuint programID;
	GLFWwindow* window;
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	void init();
	void initGLFW();
	void initGLEW();
	void sendMVP();
	static void KI::error_callback(int error, const char* description) {
		fputs(description, stderr);
	}
	void start();
public:
	KI(void);
	~KI(void);
};

