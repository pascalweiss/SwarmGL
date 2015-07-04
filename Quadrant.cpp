#include "Quadrant.h"
#include <iostream>
#include "Globals.h"
#include <string>


Quadrant::Quadrant(QuadrantCoordinates* coordinates, double locationIntensity)
{
	this->coordinates = coordinates;
	this->locationIntensity = locationIntensity;
	glm::vec3 v = glm::vec3(0.0,0.0,0.0);
	this->influenceVector = new InfluenceVector(0, glm::vec3(0.0,0.0,0.0));
	this->calculateInfluenceVector();
}

std::vector<Particle> Quadrant::getParticles()
{	
	return std::vector<Particle>();
}

void Quadrant::setParticles(std::vector<Particle*> particles)
{
	this->particles = particles;
	this->calculateIntensity();
}

void Quadrant::calculateInfluenceVector()
{
	float x = -1 * this->coordinates->getX();
	float y = -1 * this->coordinates->getY();
	float z = -1 * this->coordinates->getZ();
	this->influenceVector->setVector(glm::vec3(x,y,z));
	this->influenceVector->setIntensity(this->calculateIntensity());
	if (DEBUG) {
	//TODO	std::cout << "Q(" + std::to_string(x);
	}
}

double Quadrant::calculateIntensity() 
{
	double particle_influence = (double)this->particles.size() * PARTICLE_INFLUENCE;
	return this->locationIntensity + particle_influence;
}



Quadrant::~Quadrant(void)
{

}
