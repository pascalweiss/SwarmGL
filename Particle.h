#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class Particle
{
private:
	bool readyForDraw;
	glm::vec3 directionVector;
	glm::vec3 positionVector;
	double velocity;
	GLuint vertexArrayIDParticle;
public:
	Particle(void);
	void draw();
	void generateParticle();
	glm::vec3 getNextPosition();
	void setDirectionVector(glm::vec3 vector);
	void setPositionVector(glm::vec3 vector);
	void setVelocity(double aVelocity);
	void toggleReadyForDraw();
	~Particle(void);
};

