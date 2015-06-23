#include "KI.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "shader.hpp"


KI::KI(void) {
	if (this->initialize() != 0) {
        assert(false);
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Background Color
    glClearColor(0.0f, 0.6f, 0.4f, 0.0f);
    // Shader auch benutzen !
	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
    glUseProgram(programID);
	this->start();
}


int KI::initialize() {
    // Initialise GLFW
    // Erst mal Fenster erzeugen
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Fehler werden auf stderr ausgegeben, s. o.
    //glfwSetErrorCallback(error_callback);
    
    // Open a window and create its OpenGL context
    // glfwWindowHint vorher aufrufen, um erforderliche Resourcen festzulegen
    window = glfwCreateWindow(1024, // Breite
                                          768,  // Hoehe
                                          "CG - Tutorial", // Ueberschrift
                                          NULL,  // windowed mode
                                          NULL); // shared window
    
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Make the window's context current (wird nicht automatisch gemacht)
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    // GLEW ermöglicht Zugriff auf OpenGL-API > 1.1
    glewExperimental = true; // Needed for core profile
    
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    return 0;
}
/*
int KI::initialize() {
    // Initialise GLFW
    // Erst mal Fenster erzeugen
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    
    // Fehler werden auf stderr ausgegeben, s. o.
    //glfwSetErrorCallback(error_callback);
    
    // Open a window and create its OpenGL context
    // glfwWindowHint vorher aufrufen, um erforderliche Resourcen festzulegen
	window = glfwCreateWindow(1024, // Breite
                                          768,  // Hoehe
                                          "CG - Tutorial", // Ueberschrift
                                          NULL,  // windowed mode
                                          NULL); // shared window
    
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Make the window's context current (wird nicht automatisch gemacht)
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    // GLEW ermöglicht Zugriff auf OpenGL-API > 1.1
    glewExperimental = true; // Needed for core profile
    
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
		return 1;
    }
	return 0;
}
*/
void KI::start() {
	for (;;) {
		std::cout << "WAT";
	}
}

void KI::error_callback(int error, const char* description) {
    fputs(description, stderr);
}

KI::~KI(void)
{
}
