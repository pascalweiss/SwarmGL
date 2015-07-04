#include "Quadrant.h"
#include <iostream>
#include "Globals.h"


Quadrant::Quadrant(QuadrantCoordinates* coordinates)
{
	this->coordinates = coordinates;
	glm::vec3 v = glm::vec3(0.0,0.0,0.0);
	this->influenceVector = new InfluenceVector(0, glm::vec3(0.0,0.0,0.0));
}

std::vector<Particle> Quadrant::getParticles()
{	
	return std::vector<Particle>();
}

void Quadrant::setParticles(Particle particles[])
{
}

void Quadrant::calculateInfluenceVector()
{
	float x = -1 * this->coordinates->getX();
	float y = -1 * this->coordinates->getY();
	float z = -1 * this->coordinates->getZ();	
	this->influenceVector->setVector(glm::vec3(x,y,z));
	this->influenceVector->setIntensity(this->calculateIntensity());
}

double Quadrant::calculateIntensity() 
{
	double particle_influence = (double)this->particles.size() * PARTICLE_INFLUENCE;
	
}



Quadrant::~Quadrant(void)
{

}
