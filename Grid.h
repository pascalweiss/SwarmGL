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
	void addQuadrant(int x, int y, int z, int dimensionLength);
	double calculateLocationIntensity(int dimensionLength, QuadrantCoordinates * coordinates); 
public:
	Grid(int dimensionLength);
	Quadrant* getQuadrantAt(int x, int y, int z);
	void calculateNewParticlePositions();
	void registerParticles();
	void moveParticles();
	void applyInfluenceVectors();
	void drawParticles();
	void clearQuadrants();
	~Grid(void);
private:
	void generateInfluenceVectors();
	float getRandomFloat(float min, float max);
	int getIndex(int absPos);
	int getFloatAsAbsInt(float f);
	glm::vec3 getRandomVector(float min, float max);
	bool inGrid(Particle* p);
};

