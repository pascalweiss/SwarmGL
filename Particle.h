#pragma once
#include <glm/glm.hpp>

class Particle
{
private:
	bool readyForDraw;
	glm::vec3 directionVector;
	glm::vec3 positionVector;
	double velocity;
public:
	Particle(void);
	void draw();
	glm::vec3 getNextPosition();
	void setDirectionVector(glm::vec3 vector);
	void setPositionVector(glm::vec3 vector);
	void setVelocity(double velocity);
	void toggleReadyForDraw();
	~Particle(void);
};

