#pragma once
#include "QuadrantCoordinates.h"
#include "Particle.h"
#include "InfluenceVector.h"
#include <vector>

class Quadrant
{
private:
	std::vector<Particle> particles;
	InfluenceVector* influenceVector;
	QuadrantCoordinates* coordinates;
	double locationIntensity;
	double calculateIntensity();
	
public:
	Quadrant(QuadrantCoordinates* coordinates, double locationIntensity);
	std::vector<Particle> getParticles();
	void setParticles(Particle particles[]);
	void calculateInfluenceVector();
	~Quadrant(void);
};

