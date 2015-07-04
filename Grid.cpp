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
		for (int x = 0; x < dimensionLength; x++) {
			vector <vector<Quadrant *>> v;
			this->quadrantVector.push_back(v);
			for (int y = 0; y < dimensionLength; y++) {
				vector <Quadrant*> w;
				this->quadrantVector[x].push_back(w);
				for (int z = 0; z < dimensionLength; z++) {
					this->addQuadrant(x,y,z,dimensionLength);
				}
			}
		}
	}
	else {
		std::cout << "dimensionLength must be a odd number";
		assert(false);
	}
}

void Grid::addQuadrant(int x, int y, int z, int dimensionLength) {
	if (dimensionLength % 2 == 1) {
		int startCoordinate = -1 * (dimensionLength - 1) / 2;
		QuadrantCoordinates* coordinates = new QuadrantCoordinates(
						(float)x + startCoordinate, 
						(float)y + startCoordinate, 
						(float)z + startCoordinate);
		double locationIntensity = this->calculateLocationIntensity(dimensionLength, coordinates);
		this->quadrantVector[x][y].push_back(new Quadrant(coordinates, locationIntensity));
	} 
}

double Grid::calculateLocationIntensity(int dimensionLength, QuadrantCoordinates * coordinates) 
{
	if (dimensionLength % 2 == 1) {
		int maxCoordinate = (dimensionLength - 1) / 2;
		double biggestCoordinate = coordinates->getBiggestAbsolute();
		return biggestCoordinate / maxCoordinate;
	}
}

void Grid::initParticles()
{
	Particle* particle;
	for (int i = 0; i < NUMBER_OF_PARTICLES; i++) 
	{
		//particle = new Particle();
		//this->particleVector.push_back(particle);
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
