#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Particle
{
private:
	bool readyForDraw;
	
	double velocity;
	float len;
	
	glm::vec3 directionVector;
	GLuint vertexArrayIDParticle;
	std::vector<glm::vec3> positionVector; //move all points when translate Particle

public:
	Particle();
	Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector, float aLen);
				//get normal vector to calculate base points of the polygon, 
				//peak is calculated by positionVector + directionVector * len
	
	void draw();
	void move();
	void generateParticle();
	void setDirectionVector(glm::vec3 vector);
	void setPositionVector(std::vector<glm::vec3> vector);
	void setVelocity(double velocity);
	void toggleReadyForDraw();
	
	std::vector<glm::vec3> getNextPosition();
	
	~Particle(void);

private:
	void setPeak(glm::vec3 basePosVector);
	
	glm::vec3 normalizeVector(glm::vec3 toNormalize);
};

