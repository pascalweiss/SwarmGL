#pragma once
#include "Quadrant.h"
#include "Particle.h"
class Grid
{
private:
	Quadrant quadrantArray[][][];
	Particle particleArray[];
public:
	Grid(int numberOfQuadrants);
	Quadrant getQuadrantAt(QuadrantCoordinates quadCoordinates);
	void calculateNewParticlePositions();
	void registerAndDrawParticles();
	~Grid(void);
private:
	void generateInfluenceVectors();
};

