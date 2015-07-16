/**
 SwarmGL
 =======
 SwarmGLFacade.h 
 
 This class manages the basic configurations for the simulation.
 On the one hand it initializes all requirements for the OpenGL visualisation
 and runs the drawing loop. On the other hand it is the starting point
 for all logic operations, to make the particles behave in a appropriate way.
 The Program starts by calling the constructor.
 
 @author Tom Bisson, Pascal Weiß
 @date   16.07.2015
 
 */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

class SwarmGLFacade
{
private:
	GLuint programID;
	GLFWwindow* window;
	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
    
	void init();
    
    /**
        Initializes GLFW
     */
	void initGLFW();

    /**
     Initializes GLEW
     */
	void initGLEW();
    /**
     This method runs the drawing loop. With every iteration, 
     the next position for every particle is calculated
     
    */
    void sendMVP();
    static void error_callback(int error, const char* description) {
        fputs(description, stderr);
    }
    
    /**
     The main loop. This is where the drawing happens, and the 
     initial methods for the logic is called.
     */
	void start();
    
public:
    /**
     Constructor
     */
	SwarmGLFacade(void);
	~SwarmGLFacade(void);
};

