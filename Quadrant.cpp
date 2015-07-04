#include "Quadrant.h"


Quadrant::Quadrant(QuadrantCoordinates* coordinates)
{
	this->coordinates = coordinates;
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
}

Quadrant::~Quadrant(void)
{
}
