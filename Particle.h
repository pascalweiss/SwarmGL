#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Particle
{
private:
	bool readyForDraw;
	
	float velocity;
	float len;
	
	GLuint vertexbuffer;
	GLuint colorbuffer;

	glm::vec3 directionVector;
	GLuint vertexArrayIDParticle;
	std::vector<glm::vec3> positionVector; //move all points when translate Particle
	glm::vec3 basePositionVector;

public:
	Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector, float aLen);
	Particle(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector, float aLen);
				//get normal vector to calculate base points of the polygon, 
				//peak is calculated by positionVector + directionVector * len
	
	void draw();
	void move();
	void generateParticle();
	void addToDirectionVector(glm::vec3 vector);
	void setPositionVector(std::vector<glm::vec3> vector);
	void setVelocity(float velocity);
	void toggleReadyForDraw();
	void clearBuffers();
	glm::vec3 getBasePosition();
	glm::vec3 getDirectionVector();
	std::vector<glm::vec3> getNextPosition();
	
	~Particle(void);

private:
	void init(glm::vec3 basePosVector, glm::vec3 aDirectionVector, glm::vec3 normVector, float aLen);
	void setPeak(glm::vec3 basePosVector);
	void setBasePositions(glm::vec3 basePosVector, glm::vec3 normVector);
	
	glm::vec3 normalizeVector(glm::vec3 toNormalize);
	glm::vec3 getUprightNormVector(glm::vec3 toNorm);

	glm::vec3 normVector; //DEL
};

