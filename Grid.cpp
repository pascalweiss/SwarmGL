#include "Grid.h"
#include "Globals.h"

Grid::Grid(int dimensionLength): particleVector(), quadrantVector()
{
	this->initQuadrants(dimensionLength);
	this->initParticles();
}

void Grid::initQuadrants(int dimensionLength)
{
	for (int x = 0; x < dimensionLength; x++) {
		vector <vector<Quadrant *>> v;
		this->quadrantVector.push_back(v);
		for (int y = 0; y < dimensionLength; y++) {
			vector <Quadrant*> w;
			this->quadrantVector[x].push_back(w);
			for (int z = 0; z < dimensionLength; z++) {
				QuadrantCoordinates* coordinates = new QuadrantCoordinates((double)x, (double)y, (double)z);
				this->quadrantVector[x][y].push_back(new Quadrant(coordinates));
			}
		}
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
