#include "Grid.h"


Grid::Grid(int dimensionLength)
{
	this->initQuadrants(dimensionLength);

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
