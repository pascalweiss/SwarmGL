/**
 SwarmGL
 =======
 Grid.h
 
 This class divides the space into three-dimensional quadrants. This way
 it is possible to find out, how many particles are next to each other, and
 how far they are away from the center. It also holds references to all particles,
 so it has methods for operations on all particles (like clearParticleBuffers)
 
 @author Tom Bisson, Pascal Weiß
 @date   16.07.2015
 */

#pragma once
#include "Quadrant.h"
#include "Particle.h"
#include <vector>

using namespace std;


class Grid
{
    // Variables
public:
    Grid(int dimensionLength);
    ~Grid(void);
    
private:
	vector<vector<vector<Quadrant*>>> quadrantVector;
	vector<Particle*> particleVector;

    // Methods
public:
    Quadrant* getQuadrantAt(int x, int y, int z);
    
    /**
     This is where every particle is registered in
     on of the quadrants, depending on its location.
     */
    void registerParticles();
    
    /**
     Goes over every particle and moves it in the
     respective direction, with the respective
     velocity.
     */
    void moveParticles();
    
    /**
     The movement of every particle is dependent on
     its location (the quadrant, where it is registered)
     and the other particles, near to it. This is where
     each particle becomes its next movement direction.
     */
    void applyInfluenceVectors();
    
    /**
     Goes over every particle and draws it.
     */
    void drawParticles();
    
    /**
     All particles are removed from their respective
     quadrant.
     */
    void clearQuadrants();
    
    /**
     Goes over every particle and deletes the respective
     buffers.
     */
    void clearParticleBuffers();

private:
    void initQuadrants(int dimensionLength);
    void initParticles();
    void addQuadrant(int x, int y, int z, int dimensionLength);
    double calculateLocationIntensity(int dimensionLength, QuadrantCoordinates * coordinates);
	void generateInfluenceVectors();
	float getRandomFloat(float min, float max);
	int getIndex(int absPos);
	int getFloatAsAbsInt(float f);
	glm::vec3 getRandomVector(float min, float max);
	bool inGrid(Particle* p);
};

