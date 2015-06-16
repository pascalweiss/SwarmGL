#pragma once
#include <glm/glm.hpp>
class InfluenceVector
{
private:
	glm::vec3 vector;
	double influence;
public:
	InfluenceVector(void);
	glm::vec3 getEffectiveVector();
	~InfluenceVector(void);
};

