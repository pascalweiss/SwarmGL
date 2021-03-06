#include "Quadrant.h"
#include <iostream>
#include "Globals.h"
#include <string>
#include <time.h>

Quadrant::Quadrant(QuadrantCoordinates* coordinates, double locationIntensity):particles()
{
	this->coordinates = coordinates;
	this->locationIntensity = locationIntensity;
	glm::vec3 v = glm::vec3(0.0,0.0,0.0);
	this->influenceVector = new InfluenceVector(0, glm::vec3(0.0,0.0,0.0));
	this->calculateInfluenceVector();
	srand((unsigned) time(NULL));
}

std::vector<Particle> Quadrant::getParticles()
{	
	return std::vector<Particle>();
}

void Quadrant::addParticle(Particle *particle) 
{
	this->particles.push_back(particle);
}

void Quadrant::clearParticles() 
{
	this->particles.clear();
}

void Quadrant::setParticles(std::vector<Particle*> particles)
{
	this->particles = particles;
}

void Quadrant::calculateInfluenceVector()
{
	float x = -1 * this->coordinates->getX();
	float y = -1 * this->coordinates->getY();
	float z = -1 * this->coordinates->getZ();
	this->influenceVector->setVector(glm::vec3(x,y,z));
	this->influenceVector->setIntensity(this->calculateIntensity());
}

double Quadrant::calculateIntensity() 
{
	double particle_influence = (double)this->particles.size();
	if (DEBUG_FLAG) {
		std::cout 
			<< "Q(" 
			<< this->coordinates->getX() 
			<< "," 
			<< this->coordinates->getY() 
			<< "," 
			<< this->coordinates->getZ()
			<< ") Intensity: " 
			<< particle_influence + this->locationIntensity
			<< std::endl;
	}
	return this->locationIntensity + particle_influence;
}

glm::vec3 Quadrant::getPossibleDirections(Particle* p)
{
	float DimHalf = DIMENSION_LENGTH / 2;
	float x = getRandomFloat(-DimHalf + p->getBasePosition().x, 
							 DimHalf - p->getBasePosition().x);
	float y = getRandomFloat(-DimHalf + p->getBasePosition().y, 
							 DimHalf - p->getBasePosition().y);
	float z = getRandomFloat(-DimHalf + p->getBasePosition().z, 
							 DimHalf - p->getBasePosition().z);
	return glm::vec3(x, y, z);
}

float Quadrant::getRandomFloat(float min, float max)
{
	float f = (float)rand() / RAND_MAX;
	return min + f * (max - min);
}

int Quadrant::getRandomInt(int min, int max)
{
	return std::rand() % (int) max - min;
}

void Quadrant::applyInflueneceVector()
{
    /*
    Alternative Algorithm
    
    glm::vec3 effectiveVector = this->influenceVector->getEffectiveVector(this->particles);
    for (int i = 0; i < particles.size(); i++) {
        if (this->particles.size() >= PANIC_THRESHOLD && getRandomInt(0, PANIC_DAMPING) == 1)
        {
            particles[i]->setVelocity(PANIC_VELOCITY);
            particles[i]->addToDirectionVector(getPossibleDirections(this->particles[i]));
        }
        else {
            particles[i]->setVelocity(VELOCITY);
            particles[i]->addToDirectionVector(effectiveVector);
        }
    }
     */
    
    if (this->particles.size() >= PANIC_THRESHOLD) {
        if (getRandomInt(0, PANIC_DAMPING) == 1) {
            for (int i = 0; i < particles.size(); i++) {
                particles[i]->setVelocity(PANIC_VELOCITY);
                particles[i]->addToDirectionVector(getPossibleDirections(this->particles[i]));
            }
        }
        
        else if (MODE == 1) {
            glm::vec3 effectiveVector = this->influenceVector->getEffectiveVector(this->particles);
            for (int i = 0; i < particles.size(); i++) {
                particles[i]->setVelocity(VELOCITY);
                particles[i]->addToDirectionVector(effectiveVector);
                
            }
        }
    }
    else {
        glm::vec3 effectiveVector = this->influenceVector->getEffectiveVector(this->particles);
        for (int i = 0; i < particles.size(); i++) {
            particles[i]->setVelocity(VELOCITY);
			particles[i]->addToDirectionVector(effectiveVector);
    
        }
    }
}

Quadrant::~Quadrant(void)
{
	delete coordinates;
}
