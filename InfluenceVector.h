#pragma once
#include <glm/glm.hpp>
class InfluenceVector
{
private:
	glm::vec3 vector;
	double intensity;
public:
	InfluenceVector(double intensity, glm::vec3 vector);
	void setVector(glm::vec3 v);
	void setIntensity(double i);
	glm::vec3 getEffectiveVector();
	glm::vec3 getVector();
	~InfluenceVector(void);
};
