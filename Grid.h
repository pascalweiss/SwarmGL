#pragma once
#include "Quadrant.h"
#include "Particle.h"
#include <vector>

using namespace std;

class Grid
{
private:
	vector<vector<vector<Quadrant*>>> quadrantVector;
	vector<Particle*> particleVector;
	void initQuadrants(int dimensionLength);
	void initParticles();
public:
	Grid(int dimensionLength);
	Quadrant* getQuadrantAt(int x, int y, int z);
	void calculateNewParticlePositions();
	void registerAndDrawParticles();
	~Grid(void);
private:
	void generateInfluenceVectors();
};

