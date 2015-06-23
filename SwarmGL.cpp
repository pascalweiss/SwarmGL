// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

////////////////////////////////////neu, nicht löschen
#include "KI.h"
////////////////////////////////////



int main(void) {
	KI *ki = new KI();

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include "objloader.hpp"

#include "texture.hpp"

#include "shader.hpp"

// Wuerfel und Kugel
#include "objects.hpp"
#include "Particle.h"
using namespace glm;


// Diese Drei Matrizen global (Singleton-Muster), damit sie jederzeit modifiziert und
// an die Grafikkarte geschickt werden koennen
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;

GLuint programID;
GLFWwindow* window;
GLuint VertexArrayIDTeapot;
GLuint Texture;
std::vector<glm::vec3> vertices;
GLuint uvbuffer; // Hier alles analog f¸r Texturkoordinaten in location == 1 (2 floats u und v!)


void error_callback(int error, const char* description) {
    fputs(description, stderr);
}



void sendMVP() {
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model;
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform, konstant fuer alle Eckpunkte
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);
}


int initialize() {
    // Initialise GLFW
    // Erst mal Fenster erzeugen
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    
    // Fehler werden auf stderr ausgegeben, s. o.
    glfwSetErrorCallback(error_callback);
    
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

int main(void) {
    if (initialize() != 0) {
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Background Color
    glClearColor(0.0f, 0.6f, 0.4f, 0.0f);
    // Shader auch benutzen !
    
    
    
    glm::vec3 lightPos = glm::vec3(4,4,-4);
    glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);
    
	
    // Eventloop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Swap buffers
        // Es gibt 2 Buffer
        // Buffer 1: Wird mit Frequenz des Bildschirms ausgelesen und auf Bildschirm angezeigt
        // Buffer 2: Fragment Shader schreibt rein. wird in Buffer 1 eingefügt, sobald glfwSwapBuffers aufgerufen wird.
        glfwSwapBuffers(window);
		drawTeapot();
        // Poll for and process events 
        glfwPollEvents();
    }
    glDeleteBuffers(1, &uvbuffer);
    glDeleteTextures(1, &Texture);
    glDeleteProgram(programID);

	

    glfwTerminate();
    return 0;
>>>>>>> 1a6dd7074fa93fb019ebd4c7a4a37984a935a776
}
