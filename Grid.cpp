#include "Grid.h"
#include "Globals.h"

Grid::Grid(int dimensionLength): particleVector()
{
	this->initQuadrants(dimensionLength);
	this->initParticles();
	particleVector.push_back(new Particle());
}

void Grid::initQuadrants(int dimensionLength)
{
	this->quadrantVector.resize(dimensionLength);
	for(int i = 0; i < dimensionLength; i++)
	{
		this->quadrantVector[i].resize(dimensionLength);
		for(int j = 0; j < dimensionLength; j++)		
		{
			this->quadrantVector[i][j].resize(dimensionLength, new Quadrant());
		}
	}
}

void Grid::initParticles()
{
	for (int i = 0; i < NUMBER_OF_PARTICLES; i++) 
	{
		//this->particleVector.push_back(new Particle());
	}
}

Quadrant Grid::getQuadrantAt(QuadrantCoordinates quadCoordinates)
{
	return Quadrant();
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
