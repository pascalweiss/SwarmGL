/**
 SwarmGL
 =======
 Quadrant.h
 
 Each quadrant holds a various number of particles.
 The number of the particles has an impact on the movement
 of the particles, since the direction of the movement of
 a singe particle becomes random, when there are too many
 other particles in the same quadrant. This way, panic shall
 be simulated (You can change the threshold for the panic reaction
 with the macro PANIC_THRESHOLD, in Globals.json).
 
 @author Tom Bisson, Pascal Weiß
 @date   16.07.2015
 */

#pragma once
#include "QuadrantCoordinates.h"
#include "Particle.h"
#include "InfluenceVector.h"
#include <vector>

 
class Quadrant
{
    //Variables
private:
	std::vector<Particle*> particles;
	InfluenceVector* influenceVector;
	QuadrantCoordinates* coordinates;
	double locationIntensity;
	double calculateIntensity();
	
    //Methods
public:
    /**
     The Constructor
     */
	Quadrant(QuadrantCoordinates* coordinates, double locationIntensity);
    
    /**
     Getter for the particles.
     @return a vector of all particles, registered in the quadrant.
     */
	std::vector<Particle> getParticles();
    
    /**
     Removes all particles from the quadrant.
     */
	void clearParticles();
    
    /**
     Adds a single particle to 'particles'
     @param particle - the particle to add.
     */
	void addParticle(Particle* particle);
    
    /**
     a setter for 'particles'
     @param particles - the vector of particles to set.
     */
	void setParticles(std::vector<Particle*> particles);
    
    /**
     Adds the respective influence vector to every 
     particle in the quadrant.
     */
	void applyInflueneceVector();
	~Quadrant(void);
private:
	glm::vec3 getPossibleDirections(Particle* p);
	float getRandomFloat(float min, float max);
    void calculateInfluenceVector();
	int getRandomInt(int min, int max);
};

