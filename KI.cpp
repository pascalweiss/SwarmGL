#include "KI.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "shader.hpp"
#include "Grid.h"


KI::KI(void) {
	this->init();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.6f, 0.4f, 0.0f);
	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
    glUseProgram(programID);
	this->start();
}

void KI::init() {
    initGLFW();
	initGLEW();
}

void KI::initGLFW() {
	if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
	glfwSetErrorCallback(KI::error_callback);
	window = glfwCreateWindow(1024, 768, "SwarmGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
		fprintf(stderr, "Failed to initialize GLFW\n");
        assert(false);
    }
    glfwMakeContextCurrent(window);
}

void KI::initGLEW() {
	glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
		assert(false);
    }
}

void KI::start() {
	Grid* grid = new Grid(3);
	for (;;) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
        glfwPollEvents();
	}
}

KI::~KI(void)
{
}
