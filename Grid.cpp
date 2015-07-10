#include "Grid.h"
#include "Globals.h"
#include <iostream>
#include "time.h"

Grid::Grid(int dimensionLength): particleVector(), quadrantVector()
{
	this->initQuadrants(dimensionLength);
	this->initParticles();
	srand((unsigned) time(NULL));
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
		return biggestCoordinate / maxCoordinate / 10;
	}
	return 0;
}

void Grid::initParticles()
{
	Particle* particle;
	float max = DIMENSION_LENGTH / 2;
	float min = -max;
	for (int i = 0; i < NUMBER_OF_PARTICLES; i++) 
	{
		particleVector.push_back(new Particle(getRandomVector(min, max), 
											  getRandomVector(min, max), 
											  PARTICLE_LENGTH));
	}
}

Quadrant* Grid::getQuadrantAt(int x, int y, int z)
{
	return this->quadrantVector[x][y][z];
}

void Grid::calculateNewParticlePositions()
{

}

void Grid::clearQuadrants() 
{
	int length = this->quadrantVector.size();
	for (int x = 0; x < length; x++) 
	{
		for (int y = 0; y < length; y++) 
		{
			for (int z = 0; z < length; z++) 
			{
				this->quadrantVector[x][y][z]->clearParticles();		
			}
		}
	}
}

void Grid::registerParticles() 
{
	glm::vec3 v;
	Particle *p;
	for (int i = 0; i < particleVector.size(); i++)
	{	
		v = particleVector[i]->getBasePosition();
		p = particleVector[i];
		if(inGrid(p))
			quadrantVector[getIndex(v.x)][getIndex(v.y)][getIndex(v.z)]->addParticle(p);
		
			
	}
}

bool Grid::inGrid(Particle* p)
{
	glm::vec3 basePos = p->getBasePosition();
	bool ret = true;
	if (getFloatAsAbsInt(basePos.x) >= DIMENSION_LENGTH / 2 || 
		getFloatAsAbsInt(basePos.y) >= DIMENSION_LENGTH / 2 ||
		getFloatAsAbsInt(basePos.z) >= DIMENSION_LENGTH / 2)
		ret = false;
	return ret;
}

int Grid::getFloatAsAbsInt(float f)
{
	int ret = f / 1;
	if (ret < 0)
		return ret * -1;
	return ret;
}

int Grid::getIndex(int absPos)
{
	return absPos + this->quadrantVector.size() / 2;
}

void Grid::moveParticles()
{
	applyInfluenceVectors();
	for (int i = 0; i < particleVector.size(); i++)
		particleVector[i]->move();
}

void Grid::applyInfluenceVectors()
{
	for (int x = 0; x < quadrantVector.size(); x++)
	{
		for (int y = 0; y < quadrantVector.size(); y++)
		{
			for (int z = 0; z < quadrantVector.size(); z++)
			{
				quadrantVector[x][y][z]->applyInflueneceVector();
			}
		}
	}
}

void Grid::drawParticles()
{
	for (int i = 0; i < particleVector.size(); i++)
		particleVector[i]->draw();
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

float Grid::getRandomFloat(float min, float max)
{
	float f = (float)rand() / RAND_MAX;
	return min + f * (max - min);
}

glm::vec3 Grid::getRandomVector(float min, float max)
{
	return glm::vec3(this->getRandomFloat(min, max), 
					 this->getRandomFloat(min, max),
					 this->getRandomFloat(min, max));
}