/**
 SwarmGL
 =======
 InfluenceVector.h
 
 This class holds the information about the vector, that
 influences the movement of the particles contained by a
 quadrant.
 
 @author Tom Bisson, Pascal Weiß
 @date   16.07.2015
 */

#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Particle.h"


class InfluenceVector
{
private:
    /**
     A three-dimensional vector, used for influencing the 
     movement direction of particles.
     */
	glm::vec3 vector;
    
    /**
     This value predicates, how much the movement a particle 
     is influenced by the vector.
     */
	float intensity;
    
public:
    /**
     Constructor
     @param intensity   - used as the 'intensity'
     @param vector      - used as the 'vector'
     */
    InfluenceVector(double intensity, glm::vec3 vector);

    /**
     A setter for 'vector'
     @param v - becomes the new 'vector'
     */
	void setVector(glm::vec3 v);
    
    /**
     A setter for intensity
     @param i - becomes the new 'intensity'
     */
	void setIntensity(double i);
    
    /**
     This method takes a vector of particles (usually all particles
     in a quadrant), combines the direction vectors of all particles
     with each other and finally combines the result with the 
     private 'vector' variable. The result can be used for the movement
     of each particle in one iteration. 
     @param p the particles that shall influence the effective vector
     @return the effective vector for the particles in 'p'.
     
     */
	glm::vec3 getEffectiveVector(std::vector<Particle*> p);
    
    /**
     Getter method for 'vector'.
     @return the three dimensional vector
     */
	glm::vec3 getVector();
	~InfluenceVector(void);
private:
	glm::vec3 normalizeVector(glm::vec3 toNormalize);
};
