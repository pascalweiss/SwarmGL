#include "InfluenceVector.h"
#include "Globals.h"


InfluenceVector::InfluenceVector(double intensity, glm::vec3 vector)
{
	this->intensity = intensity;
	this->vector = this->normalizeVector(vector);
}

glm::vec3 InfluenceVector::getVector() 
{
	return this->vector;
}

void InfluenceVector::setVector(glm::vec3 v) 
{
	this->vector = v;
}
void InfluenceVector::setIntensity(double i) 
{
	this->intensity = i;
}

glm::vec3 InfluenceVector::getEffectiveVector(std::vector<Particle*> p)
{
	if (this->intensity >= 1.0 / OPENNESS)
		return this->vector;
	glm::vec3 ret = this->vector * this->intensity;
	for (int i = 0; i < p.size(); i++)
		ret += p[i]->getDirectionVector() * ((1 - intensity) / p.size() * OPENNESS);
	return normalizeVector(ret);
}

glm::vec3 InfluenceVector::normalizeVector(glm::vec3 toNormalize)
{
	if (toNormalize.x != 0 && toNormalize.y != 0 && toNormalize.z != 0) 
		return glm::normalize(toNormalize);
	return toNormalize;
}

InfluenceVector::~InfluenceVector()
{
}

