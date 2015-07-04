#include "Grid.h"
#include "Globals.h"

Grid::Grid(int dimensionLength): particleVector(), quadrantVector()
{
	this->initQuadrants(dimensionLength);
	this->initParticles();
}

void Grid::initQuadrants(int dimensionLength)
{
	this->quadrantVector.resize(dimensionLength);

	for (int x = 0; x < dimensionLength; x++) {
		this->quadrantVector.push_back(vector<vector<Quadrant*>>(dimensionLength));
		for (int y = 0; y < dimensionLength; y++) {
			for (int z = 0; z < dimensionLength; z++) {
			//	this->quadrantVector[x][y][z] = new Quadrant();
			}
		}
	}
	/*for(int x = 0; x < dimensionLength; x++)
	{
		this->quadrantVector[x].resize(dimensionLength);
		for(int y = 0; y < dimensionLength; y++)		
		{
			this->quadrantVector[x][y].resize(dimensionLength, new Quadrant());
		}
	}*/
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
}


//private Methods
void Grid::generateInfluenceVectors()
{
}
