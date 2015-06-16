#pragma once
#include "QuadrantCoordinates.h"
#include "Particle.h"
#include "InfluenceVector.h"
class Quadrant
{
private:
	Particle particles[];
	InfluenceVector influenceVector;
	QuadrantCoordinates coordinates;
public:
	Quadrant(void);
	Particle[] getParticles();
	void setParticles(Particle particles[]);
	void calculateInfluenceVector();
	~Quadrant(void);
};

