/**
 SwarmGL
 =======
 Particle.h
 
 This class represents a particle. It contains all information
 to draw the particle in the right location, with the right orientation
 and in a proper way.
 
 @author Tom Bisson, Pascal Weiß
 @date   16.07.2015
 */

#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Particle
{
    // Variables
private:
	bool readyForDraw;
	float velocity;
	float len;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	glm::vec3 directionVector;
	GLuint vertexArrayIDParticle;
	std::vector<glm::vec3> positionVector;
    glm::vec3 basePositionVector;
    
    // Methods
public:
    /**
     Constructor
     @param basePosVector     - The position where the particle is drawn the first time
     @param aDirectionVector  - The direction vector, giving the direction of the first
                                movement of the particle
     */
	Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector);
    
    /**
     draws the particle
     */
	void draw();
    
    /**
     Moves the particle with its 'velocity' and its 'directionVector'
     */
	void move();
    
    /**
     Receives a influence vector and adds it to the current 'directionVector'
     @param vector - the influence vector
     */
	void addToDirectionVector(glm::vec3 vector);
    
    /**
     Setter for 'positionVector'
     @param vector
     */
	void setPositionVector(std::vector<glm::vec3> vector);
    
    /**
     Setter for 'velocity'
     @param velocity
     */
	void setVelocity(float velocity);
    
	void toggleReadyForDraw();
    
    /**
     Deletes all buffers
     */
	void clearBuffers();
    
    /**
     Getter for 'basePosition'
     @return basePosition
     */
	glm::vec3 getBasePosition();
    
    /**
     Getter for 'directionVector'
     @return directionVector
     */
	glm::vec3 getDirectionVector();
	std::vector<glm::vec3> getNextPosition();
	
	~Particle(void);

private:
	void init(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector);
	void setPeak(glm::vec3 basePosVector);
	void setBasePositions(glm::vec3 basePosVector, glm::vec3 normVector);
    void generateParticle();
	glm::vec3 normalizeVector(glm::vec3 toNormalize);
	glm::vec3 getUprightNormVector(glm::vec3 toNorm);

};

