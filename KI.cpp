#include "KI.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "shader.hpp"
#include "Grid.h"
#include "objects.hpp"
#include "Globals.h"


KI::KI(void) {
	this->init();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
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
	Grid* grid = new Grid(DIMENSION_LENGTH);
	glEnableVertexAttribArray(0); // siehe layout im vertex shader: location = 0 
	glVertexAttribPointer(0,  // location = 0 
		      3,  // Datenformat vec3: 3 floats fuer xyz 
		      GL_FLOAT, 
		      GL_FALSE, // Fixedpoint data normalisieren ?
		      0, // Eckpunkte direkt hintereinander gespeichert
		      (void*) 0);
	
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		View = glm::lookAt(glm::vec3(0,0,21), // Camera is at (0,0,-5), in World Space, Punkt d Betrachters
						   glm::vec3(0,0,0),  // and looks at the origin, Nullpunkt
						   glm::vec3(0,1,0)); // Head is up (set to 0,-1,0 to look upside-down), sagt, wo oben ist
											  // bzw ob der Betrachter sich in Schräglage befindet
		Model = glm::mat4(1.0f);
		grid->moveParticles();
		grid->clearQuadrants();
		grid->registerParticles();

		sendMVP();
		grid->applyInfluenceVectors();
		grid->drawParticles();
		glfwSwapBuffers(window);
        glfwPollEvents();
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
}

void KI::sendMVP()
{
	glm::mat4 MVP = Projection * View * Model; 
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
}

KI::~KI(void)
{
	delete window;
	
}
