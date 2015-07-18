#include "SwarmGLFacade.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "shader.hpp"
#include "Grid.h"
#include "objects.hpp"
#include "Globals.h"
//#include "GlobalsLoader.h"
#include <time.h>


SwarmGLFacade::SwarmGLFacade(void) {
    //GlobalsLoader::loadGlobals();
	this->init();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    programID = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
    glUseProgram(programID);
	this->start();
}

void SwarmGLFacade::init() {
    initGLFW();
	initGLEW();
}

void SwarmGLFacade::initGLFW() {
	if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
#ifdef __APPLE__ || __MACH__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwSetErrorCallback(SwarmGLFacade::error_callback);
#endif
	glfwSetErrorCallback(SwarmGLFacade::error_callback);
	window = glfwCreateWindow(1024, 768, "SwarmGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
		fprintf(stderr, "Failed to initialize GLFW\n");
        assert(false);
    }
    glfwMakeContextCurrent(window);
}

void SwarmGLFacade::initGLEW() {
	glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
		assert(false);
    }
}

void SwarmGLFacade::start() {
	Grid* grid = new Grid(DIMENSION_LENGTH);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		      3,
		      GL_FLOAT, 
		      GL_FALSE,
		      0,
		      (void*) 0);
	

    View = glm::lookAt(glm::vec3(0,0,17), // Camera is at (0,0,17), in World Space
                       glm::vec3(0,0,0),  // and looks at the origin
                       glm::vec3(0,1,0)); // Head is up (set to 0,-1,0 to look upside-down)
    Model = glm::mat4(1.0f);
    int iteration_count = 0;
    while(!glfwWindowShouldClose(window))
	{
        
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*iteration_count++;
        if (iteration_count == 100) {
            iteration_count = 0;
            GlobalsLoader::loadGlobals();
        }*/
		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
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
        grid->clearParticleBuffers();
	}
}

void SwarmGLFacade::sendMVP()
{
	glm::mat4 MVP = Projection * View * Model; 
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
}

SwarmGLFacade::~SwarmGLFacade(void)
{
	delete window;
	
}
