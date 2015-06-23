#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Particle
{
private:
	bool readyForDraw;
	glm::vec3 directionVector;
	std::vector<glm::vec3> positionVector;
	double velocity;
	GLuint vertexArrayIDParticle;
public:
	Particle(void);
	void draw();
	void move();
	void generateParticle();
	std::vector<glm::vec3> getNextPosition();
	void setDirectionVector(glm::vec3 vector);
	void setPositionVector(std::vector<glm::vec3> vector);
	void setVelocity(double velocity);
	void toggleReadyForDraw();
	~Particle(void);
};

