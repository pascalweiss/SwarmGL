#include "Grid.h"
#include "Globals.h"
#include <iostream>

Grid::Grid(int dimensionLength): particleVector(), quadrantVector()
{
	this->initQuadrants(dimensionLength);
	this->initParticles();
}

void Grid::initQuadrants(int dimensionLength)
{
	if (dimensionLength % 2 == 1) {
		int startCoordinate = (dimensionLength - 1) /2;
		for (int x = startCoordinate; x < dimensionLength; x++) {
			vector <vector<Quadrant *>> v;
			this->quadrantVector.push_back(v);
			for (int y = startCoordinate; y < dimensionLength; y++) {
				vector <Quadrant*> w;
				this->quadrantVector[x].push_back(w);
				for (int z = startCoordinate; z < dimensionLength; z++) {
					QuadrantCoordinates* coordinates = new QuadrantCoordinates((double)x, (double)y, (double)z);
					this->quadrantVector[x][y].push_back(new Quadrant(coordinates));
				}
			}
		}
	}
	else {
		std::cout << "dimensionLength must be a odd number";
		assert(false);
	}
}

void Grid::initParticles()
{
	Particle* particle;
	for (int i = 0; i < NUMBER_OF_PARTICLES; i++) 
	{
		particle = new Particle();
		this->particleVector.push_back(particle);
	}
}

Quadrant* Grid::getQuadrantAt(int x, int y, int z)
{
	return this->quadrantVector[x][y][z];
}

void Grid::calculateNewParticlePositions()
{
}

void Grid::registerAndDrawParticles()
{
}

Grid::~Grid(void)
{
	quadrantVector.clear();
	particleVector.clear();
}


//private Methods
void Grid::generateInfluenceVectors()
{
	
}
