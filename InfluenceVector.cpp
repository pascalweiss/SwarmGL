#include "InfluenceVector.h"

InfluenceVector::InfluenceVector(double intensity, glm::vec3 vector)
{
	this->intensity = intensity;
	this->vector = vector;
}

glm::vec3 InfluenceVector::getEffectiveVector()
{
	return glm::vec3(0, 0, 0);
}

glm::vec3 InfluenceVector::getVector() {
	return this->vector;
}

void InfluenceVector::setVector(glm::vec3 v) 
{
	this->vector = v;
}
void InfluenceVector::setIntensity(double i) {
	this->intensity = i;
}

InfluenceVector::~InfluenceVector()
{
}

