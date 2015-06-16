#pragma once
#include "Quadrant.h"
#include "Particle.h"
#include <vector>
class Grid
{
private:
	std::vector<std::vector<std::vector<Quadrant>>> quadrantArray;
	std::vector<Particle> particleArray;
public:
	Grid(int numberOfQuadrants);
	Quadrant getQuadrantAt(QuadrantCoordinates quadCoordinates);
	void calculateNewParticlePositions();
	void registerAndDrawParticles();
	~Grid(void);
private:
	void generateInfluenceVectors();
};

